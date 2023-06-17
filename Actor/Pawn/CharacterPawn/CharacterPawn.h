// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Pawn.h"
#include "CharacterPawn.generated.h"

/*
 * A pawn class override to take mouse input
 */
UCLASS()
class LEARNINGKITPROJECT_API ACharacterPawn : public APawn {

	GENERATED_BODY()

private:
	FRotator BaseRotation;
	UCameraComponent* CameraComponent;

public:
	// Sets default values for this pawn's properties
	ACharacterPawn();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterPawn")
	float CameraRadius = 150;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterPawn")
	float RotationLimit = 40;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Sets rotation of the FPS pawn
	void SetFpsRotation(float deltaX, float deltaY);

	// Sets rotation of the 3PS pawn
	void Set3psRotation(float deltaX, float deltaY);

};
