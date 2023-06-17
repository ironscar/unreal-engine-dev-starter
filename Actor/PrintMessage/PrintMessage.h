// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PrintMessage.generated.h"

/**
 * Prints a message with an angle for the sake of seeing logs
 */
UCLASS()
class LEARNINGKITPROJECT_API APrintMessage : public AActor {

	GENERATED_BODY()
	
	public:	
		// Sets default values for this actor's properties
		APrintMessage();

	protected:
		// Called when the game starts or when spawned
		virtual void BeginPlay() override;

	public:	
		// Called every frame
		virtual void Tick(float DeltaTime) override;

};
