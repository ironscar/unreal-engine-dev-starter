// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyDestroyerGameMode.generated.h"

/**
 * Game mode that destroys the actor at 0 index with the tag 'Destructble' every 10 seconds
 */
UCLASS()
class LEARNINGKITPROJECT_API AMyDestroyerGameMode : public AGameModeBase {

	GENERATED_BODY()

private:
	int TimeDuration = 10;

	// start the destroy timer
	void StartDestroyTimer();

public:
	// destroy the actor and restart the timer
	void DestroyDestructible();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
};
