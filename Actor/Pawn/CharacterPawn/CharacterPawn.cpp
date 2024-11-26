// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterPawn.h"
#include "Camera/CameraComponent.h"

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
	SetAnimBlueprintSpeed();
}

// Called to set speed on animation blueprint
float ACharacterPawn::SetAnimBlueprintSpeed_Implementation() {
	// Each BP ought to override this and set the animation blueprint speed with the specific implementation

	if (MovingForward == 0 && MovingSideways == 0) {
		CurrentSpeed = 0;
	} else {
		// run forward only if going forward or is 3PS when sideways
		IsActuallyRunning = (WantsToRun && MovingForward > 0) || (WantsToRun && !IsFPS && MovingSideways != 0);
		CurrentSpeed = IsActuallyRunning ? RunSpeed : WalkSpeed;
	}

	return CurrentSpeed;
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

// Getter for MoveForward
bool ACharacterPawn::isMovingForward() {
	return MovingForward != 0 || !IsFPS;
}

// Getter for MoveSideways
bool ACharacterPawn::IsMovingSideways() {
	return MovingSideways != 0 && IsFPS;
}

// Called every frame
void ACharacterPawn::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	// move actor if moving in any direction
	MovePawnPerTick();
}

float ACharacterPawn::GetTurnSpeed() {
	return IsActuallyRunning ? RunTurnSpeed : WalkTurnSpeed;
}

void ACharacterPawn::MovePawnPerTick() {
	if (CurrentSpeed > 0) {
		FRotator TargetRotation = CameraComponent->GetRelativeRotation();
		FRotator SkeletalMeshRotation = GetSkeletalMeshRotation();
		FVector SkeletalMeshForwardVector = GetSkeletalMeshForwardVector();

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

			// need to offset target rotation to direction you want to move for 3PS
			TargetRotation.Yaw += 90 * MovingSideways;
		}

		// Calculate difference in angles and normalize it to -180 to 180 as sometimes it would go to +360 and have weird cases like infinite rotations or stuttering
		float TurnAngle = SkeletalMeshRotation.Yaw - TargetRotation.Yaw;
		if (TurnAngle > 180) {
			TurnAngle = -180 + (TurnAngle - 180);
		} else if (TurnAngle < -180) {
			TurnAngle = 180 + (TurnAngle + 180);
		}
		// UE_LOG(LogTemp, Warning, TEXT("Target Rotation, Mesh Rotation, Turn Angle = %f, %f, %f"), TargetRotation.Yaw, SkeletalMeshRotation.Yaw, TurnAngle);

		if (TurnAngle != 0 && !IsFPS) {
			// set the turn speed to angle if its smaller so that we can surely get to zero
			float ActualTurnSpeed = abs(TurnAngle) < GetTurnSpeed() ? abs(TurnAngle) : GetTurnSpeed();

			// use actual relative rotation rather than overridden relative rotation
			FRotator CurrentRotation = SkeletalMeshComponent->GetRelativeRotation();

			CurrentRotation.Yaw = TurnAngle < 0 ? CurrentRotation.Yaw + ActualTurnSpeed : CurrentRotation.Yaw - ActualTurnSpeed;
			SkeletalMeshComponent->SetRelativeRotation(CurrentRotation);
		}
	}
}

// Called to rotate pawn & camera like an 3PS character
void ACharacterPawn::Set3psRotation(float deltaX, float deltaY) {
	IsFPS = false;
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

// Called to rotate pawn & camera like an FPS character
void ACharacterPawn::SetFpsRotation(float deltaX, float deltaY) {
	IsFPS = true;
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

// Called to move the pawn forward/backward
void ACharacterPawn::SetMoveForward(float value) {
	MovingForward = value;
	SetAnimBlueprintSpeed();
	// UE_LOG(LogTemp, Warning, TEXT("Pawn Forward Speed = %f, %f"), CurrentSpeed, MovingForward);
}

// Called to move the pawn sideways
void ACharacterPawn::SetMoveSideways(float value) {
	MovingSideways = value;
	SetAnimBlueprintSpeed();
	// UE_LOG(LogTemp, Warning, TEXT("FPS Pawn Side Speed = %f, %f"), CurrentSpeed, MovingSideways);
}

void ACharacterPawn::SetIsRunning(bool value) {
	WantsToRun = value;
	// UE_LOG(LogTemp, Warning, TEXT("FPS Pawn Running = %hs"), WantsToRun ? "yes" : "no");
}

// Called to set isInAir on animation blueprint
bool ACharacterPawn::SetAnimBlueprintIsInAir_Implementation() {
	// Each BP ought to override this and set the animation blueprint isInAir with the specific implementation
	return true;
}

void ACharacterPawn::SetIsJumping(bool value) {
	if (value) {
		IsInAir = SetAnimBlueprintIsInAir_Implementation();
		UE_LOG(LogTemp, Warning, TEXT("FPS Pawn Jumping = %hs"), IsInAir ? "yes" : "no");
	}
}
