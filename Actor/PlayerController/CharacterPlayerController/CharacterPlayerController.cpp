// Fill out your copyright notice in the Description page of Project Settings.

#include "LearningKitProject/Actor/Pawn/CharacterPawn/CharacterPawn.h"
#include "CharacterPlayerController.h"

void ACharacterPlayerController::PlayerTick(float DeltaTime) {
	Super::PlayerTick(DeltaTime);

	// use mouse movement to rotate
	ACharacterPawn* CharacterPawn = (ACharacterPawn*)GetPawn();
	if (CharacterPawn != nullptr) {
		float deltaX;
		float deltaY;
		this->GetInputMouseDelta(deltaX, deltaY);
		if (IsFPS) {
			CharacterPawn->SetFpsRotation(deltaX, deltaY);
		} else {
			CharacterPawn->Set3psRotation(deltaX, deltaY);
		}
	}
	
}

void ACharacterPlayerController::SetupInputComponent() {
	Super::SetupInputComponent();

	check(InputComponent != nullptr);

	// shoot binding
	InputComponent->BindAction(
		"Shoot", EInputEvent::IE_Pressed, this, &ACharacterPlayerController::Shoot);

	// change ammo binding
	InputComponent->BindAction(
		"ChangeAmmo", EInputEvent::IE_Pressed, this, &ACharacterPlayerController::ChangeAmmo);
}

void ACharacterPlayerController::Shoot() {
	// spawn a ball actor, but just log for now
	UE_LOG(LogTemp, Warning, TEXT("Shoot"));
}

void ACharacterPlayerController::ChangeAmmo() {
	// change the type of ball actor to be spawned so just log for now
	UE_LOG(LogTemp, Warning, TEXT("Change Ammo"));
}
