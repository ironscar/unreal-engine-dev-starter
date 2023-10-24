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

	/* The radius used by the camera around the pawn for third-person controls */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterPawn Camera")
	float CameraRadius = 150;

	/* Specifies the pitch (look up/down) rotation limit in degrees */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterPawn Camera")
	float RotationLimit = 40;

	/* Specifies the forward muzzle offset */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterPawn Muzzle")
	float MuzzleOffsetForward = 40;

	/* Specifies the height muzzle offset */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterPawn Muzzle")
	float MuzzleOffsetHeight = 100;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Get Muzzle Location (depends on CharacterPawn Muzzle properties)
	FVector GetMuzzleLocation();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Sets rotation of the FPS pawn
	void SetFpsRotation(float deltaX, float deltaY);

	// Sets rotation of the 3PS pawn
	void Set3psRotation(float deltaX, float deltaY);

};
