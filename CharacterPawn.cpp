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
}

// Called every frame
void ACharacterPawn::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ACharacterPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ACharacterPawn::SetRotation(float deltaX, float deltaY) {
	FRotator PawnRotation = GetActorRotation();

	// X for rotating pawn
	PawnRotation.Yaw += deltaX;

	// Y for rotating camera
	if (CameraComponent != nullptr) {
		FRotator CameraRotation = CameraComponent->GetRelativeRotation();
		CameraRotation.Pitch += deltaY;
		CameraComponent->SetRelativeRotation(CameraRotation);
	}

	SetActorRotation(PawnRotation);
}
