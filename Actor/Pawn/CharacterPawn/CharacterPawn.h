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

	float CurrentSpeed = 0;
	bool IsMovingForward = false;
	bool IsMovingSideways = false;

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

	/* Specifies speed of walking */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterPawn Animations")
	float WalkSpeed = 5;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to set speed on the animation blueprint
	UFUNCTION(BlueprintNativeEvent, Category = "CharacterPawn Animations")
	void SetAnimBlueprintSpeed(float value);

public:
	// Get Muzzle Location (depends on CharacterPawn Muzzle properties)
	FVector GetMuzzleLocation();

	// Get Forward vector using pawn direction and camera Z
	FVector GetForwardVector();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Sets rotation of the FPS pawn
	void SetFpsRotation(float deltaX, float deltaY);

	// Sets rotation of the 3PS pawn
	void Set3psRotation(float deltaX, float deltaY);

	// Sets forward/backward location of pawn
	void SetMoveForward(float value);

	// Sets sideways location of FPS pawn
	void SetFpsMoveSideways(float value);

	// Sets sideways location of 3PS pawn
	void Set3psMoveSideways(float value);

};
