// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CharacterPlayerController.generated.h"

/**
 * A character player controller to use with the character pawn
 */
UCLASS()
class LEARNINGKITPROJECT_API ACharacterPlayerController : public APlayerController {

	GENERATED_BODY()

public:
	// called every frame and delta time is the time elasped since last frame
	virtual void PlayerTick(float DeltaTime) override;

};
