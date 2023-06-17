// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MouseInputGameModeBase.generated.h"

/**
 * Game mode base class that takes mouse input
 */
UCLASS()
class LEARNINGKITPROJECT_API AMouseInputGameModeBase : public AGameModeBase {
	
	GENERATED_BODY()

public:
	AMouseInputGameModeBase();
	
};
