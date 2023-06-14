// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterPawn.h"
#include "CharacterPlayerController.h"

void ACharacterPlayerController::PlayerTick(float DeltaTime) {
	Super::PlayerTick(DeltaTime);

	// use mouse to rotate
	ACharacterPawn* CharacterPawn = (ACharacterPawn*)GetPawn();
	if (CharacterPawn != nullptr) {
		FRotator PawnRotation = CharacterPawn->GetActorRotation();
		float deltaX;
		float deltaY;
		this->GetInputMouseDelta(deltaX, deltaY);
		PawnRotation.Yaw += deltaX;
		PawnRotation.Pitch += deltaY;
		CharacterPawn->SetActorRotation(PawnRotation);
	}
}
