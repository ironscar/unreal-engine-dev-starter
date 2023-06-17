// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterPawn.h"
#include "CharacterPlayerController.h"

void ACharacterPlayerController::PlayerTick(float DeltaTime) {
	Super::PlayerTick(DeltaTime);

	// use mouse to rotate
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
