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
}

// Called every frame
void ACharacterPawn::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
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
