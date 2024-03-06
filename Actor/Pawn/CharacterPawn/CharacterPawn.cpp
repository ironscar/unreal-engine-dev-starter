// Fill out your copyright notice in the Description page of Project Settings.

#include "Camera/CameraComponent.h"
#include "CharacterPawn.h"

// Sets default values
ACharacterPawn::ACharacterPawn() {
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ACharacterPawn::BeginPlay() {
	Super::BeginPlay();

	// get camera component reference if exists in BP
	CameraComponent = FindComponentByClass<UCameraComponent>();
	if (CameraComponent != nullptr) {
		BaseRotation = CameraComponent->GetRelativeRotation();
	}

	// get skeletal mesh component reference if exists in BP
	SkeletalMeshComponent = FindComponentByClass<USkeletalMeshComponent>();

	// set walk speed to 0
	SetAnimBlueprintSpeed(0);
}

// Called to set speed on animation blueprint
void ACharacterPawn::SetAnimBlueprintSpeed_Implementation(float value) {
	// Each BP ought to override this and set the animation blueprint speed with the specific implementation
	CurrentSpeed = value;
}

// Called to get the skeletal mesh forward vector as it depends on how this mesh was exported
FVector ACharacterPawn::GetSkeletalMeshForwardVector_Implementation() {
	// Each BP ought to override this based on how their mesh aligns with the pawn directions
	return SkeletalMeshComponent->GetForwardVector();
}

// Called to get the skeletal mesh right vector as it depends on how this mesh was exported
FVector ACharacterPawn::GetSkeletalMeshRightVector_Implementation() {
	// Each BP ought to override this based on how their mesh aligns with the pawn directions
	return SkeletalMeshComponent->GetRightVector();
}

// Called to get the skeletal mesh rotation as it depends on how this mesh was exported
FRotator ACharacterPawn::GetSkeletalMeshRotation_Implementation() {
	// Each BP ought to override this based on how their mesh aligns with the pawn directions
	return SkeletalMeshComponent->GetRelativeRotation();
}

// Get Muzzle Location (depends on CharacterPawn Muzzle properties)
FVector ACharacterPawn::GetMuzzleLocation() {
	FVector MuzzleLocation = GetActorLocation();
	MuzzleLocation.Z += MuzzleOffsetHeight;
	FVector TempForward = GetSkeletalMeshForwardVector().GetClampedToMaxSize(MuzzleOffsetForward);
	MuzzleLocation += TempForward;
	return MuzzleLocation;
}

// Get Forward vector using pawn direction and camera Z
FVector ACharacterPawn::GetForwardVector() {
	FVector ForwardVector = GetSkeletalMeshForwardVector();
	FVector CameraForwardVector = CameraComponent->GetForwardVector();
	ForwardVector.Z = CameraForwardVector.Z;
	return ForwardVector;
}

// Called every frame
void ACharacterPawn::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	// move actor if moving in any direction
	if (CurrentSpeed > 0) {
		FRotator CameraRotation = CameraComponent->GetRelativeRotation();
		FRotator SkeletalMeshRotation = GetSkeletalMeshRotation();
		FVector SkeletalMeshForwardVector = GetSkeletalMeshForwardVector();
		UE_LOG(LogTemp, Warning, TEXT("Camera & Mesh angles = (%f,%f)"), CameraRotation.Yaw, SkeletalMeshRotation.Yaw);
		float TurnAngle = SkeletalMeshRotation.Yaw - CameraRotation.Yaw;

		if (MovingForward != 0) {
			FVector CameraVector = CameraComponent->GetForwardVector();
			// need to eliminate the pitch rotation aspect of the camera in this vector
			CameraVector.Z = SkeletalMeshForwardVector.Z;
			SetActorLocation((CameraVector * CurrentSpeed * MovingForward) + GetActorLocation());
		}
		if (MovingSideways != 0) {
			FVector CameraVector = CameraComponent->GetRightVector();
			// need to eliminate the pitch rotation aspect of the camera in this vector
			CameraVector.Z = SkeletalMeshForwardVector.Z;
			SetActorLocation((CameraVector * CurrentSpeed * MovingSideways) + GetActorLocation());

			// meed to set turn angle to direction you want to move for 3PS
			TurnAngle -= 90 * MovingSideways;
		}
		if (TurnAngle != 0 && is3PS) {
			UE_LOG(LogTemp, Warning, TEXT("Turn angle = %f"), TurnAngle);

			// set the turn speed to angle if its smaller so that we can surely get to zero
			float ActualTurnSpeed = TurnAngle < TurnSpeed ? TurnAngle : TurnSpeed;
			FRotator CurrentRotation = SkeletalMeshComponent->GetRelativeRotation();
			CurrentRotation.Yaw = TurnAngle < 0 ? CurrentRotation.Yaw + ActualTurnSpeed : CurrentRotation.Yaw - ActualTurnSpeed;
			SkeletalMeshComponent->SetRelativeRotation(CurrentRotation);
		}
	}
}

// Called to rotate pawn & camera like an FPS character
void ACharacterPawn::SetFpsRotation(float deltaX, float deltaY) {
	FRotator PawnRotation = GetActorRotation();
	PawnRotation.Yaw += deltaX;

	// set camera rotations
	if (CameraComponent != nullptr) {
		FRotator CameraRotation = CameraComponent->GetRelativeRotation();
		CameraRotation.Pitch = FMath::Clamp(
			CameraRotation.Pitch + deltaY,
			BaseRotation.Pitch - RotationLimit,
			BaseRotation.Pitch + RotationLimit);
		CameraComponent->SetRelativeRotation(CameraRotation);
	}

	// set pawn rotations
	SetActorRotation(PawnRotation);
}

// Called to rotate pawn & camera like an 3PS character
void ACharacterPawn::Set3psRotation(float deltaX, float deltaY) {
	if (CameraComponent != nullptr) {
		FVector CameraLocation = CameraComponent->GetRelativeLocation();

		// set camera rotations clamped by RotationLimit
		FRotator CameraRotation = CameraComponent->GetRelativeRotation();
		CameraRotation.Pitch = FMath::Clamp(
			CameraRotation.Pitch + deltaY, 
			BaseRotation.Pitch - RotationLimit,
			BaseRotation.Pitch + RotationLimit);
		CameraRotation.Yaw += deltaX;
		CameraComponent->SetRelativeRotation(CameraRotation);

		/*
		 * set camera location around pawn
		 * Adding 180 as by default it is at 180 degree position but relative rotation specifies 0
		 * Convert to radians as cos and sin functions work with radians
		 */
		CameraLocation.X = CameraRadius * cos((180 + CameraRotation.Yaw) * 3.1416 / 180);
		CameraLocation.Y = CameraRadius * sin((180 + CameraRotation.Yaw) * 3.1416 / 180);
		CameraComponent->SetRelativeLocation(CameraLocation);
	}
}

// Called to move the pawn forward/backward
void ACharacterPawn::SetMoveForward(float value) {
	MovingForward = value;
	SetAnimBlueprintSpeed(WalkSpeed * abs(value));
	UE_LOG(LogTemp, Warning, TEXT("Pawn Forward Speed = %f"), CurrentSpeed);
}

// Called to move the FPS pawn sideways
void ACharacterPawn::SetFpsMoveSideways(float value) {
	MovingSideways = value;
	SetAnimBlueprintSpeed(WalkSpeed * abs(value));
	UE_LOG(LogTemp, Warning, TEXT("FPS Pawn Side Speed = %f"), CurrentSpeed);
}

// Called to move the 3PS pawn sideways
void ACharacterPawn::Set3psMoveSideways(float value) {
	MovingSideways = value;
	is3PS = true;
	SetAnimBlueprintSpeed(WalkSpeed * abs(value));
	UE_LOG(LogTemp, Warning, TEXT("3PS Pawn Side Speed = %f"), CurrentSpeed);
}
