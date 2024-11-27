// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Pawn.h"
#include "CharacterPawn.generated.h"

/*
 * A pawn class override to take mouse and keyboard input and do associated actions
 * Assumptions:
 *  - Will be controlled by a derivative of CharacterPlayerController class
 *  - Will be inherited by a Blueprint class
 *  - Blueprint class will have a skeletal mesh and camera component as siblings
 *  - There will be an associated Animation blueprint for the skeletal mesh
 *  - Blueprint class will sync with the Anim BP by overriding the SetAnimBlueprintSpeed method
 *  - Internally, it should call the parent method, set the AnimInstance to the Anim BP if not set, and then use it to control variables on the Anim BP
 *  - Blueprint class can choose to override implementations of getting forward, right, rotation values of mesh aligned with pawn based on how its exported
 *  - Default implementation assumes mesh exported with forward as X
 *  - Provides a few blueprint properties that can be overridden for customizability
 *	- Override the DefaultPawn class in Project settings > Maps & Modes > Default modes > Selected game mode to a derivative of this class to use it
 */
UCLASS()
class LEARNINGKITPROJECT_API ACharacterPawn : public APawn {

	GENERATED_BODY()

private:
	FRotator BaseRotation;
	UCameraComponent* CameraComponent;
	USkeletalMeshComponent* SkeletalMeshComponent;

	bool IsFPS = false;
	bool IsActuallyRunning = false;
	bool IsInAir = false;
	float CurrentSpeed = 0;
	float MovingForward = 0;
	float MovingSideways = 0;
	bool WantsToRun = false;

	// to get the appropriate turn speed
	float GetTurnSpeed();

	// pawn movement processed every tick
	void MovePawnPerTick();

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
	float MuzzleOffsetHeight = 10;

	/* Specifies speed of walking */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterPawn Animations")
	float WalkSpeed = 5;

	/* Specifies speed of running */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterPawn Animations")
	float RunSpeed = 20;

	/* Specifies speed of turning while walking */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterPawn Animations")
	float WalkTurnSpeed = 10;

	/* Specifies speed of turning while running */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterPawn Animations")
	float RunTurnSpeed = 30;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Getter for MoveForward
	UFUNCTION(BlueprintCallable, Category = "CharacterPawn Animations")
	bool isMovingForward();

	// Getter for MoveSideways (only for FPS)
	UFUNCTION(BlueprintCallable, Category = "CharacterPawn Animations")
	bool IsMovingSideways();

	// Called to set speed on the animation blueprint
	UFUNCTION(BlueprintNativeEvent, Category = "CharacterPawn Animations")
	float SetAnimBlueprintSpeed();

	// Called to get the skeletal mesh forward vector as it depends on how this mesh was exported
	UFUNCTION(BlueprintNativeEvent, Category = "CharacterPawn Directions")
	FVector GetSkeletalMeshForwardVector();

	// Called to get the skeletal mesh right vector as it depends on how this mesh was exported
	UFUNCTION(BlueprintNativeEvent, Category = "CharacterPawn Directions")
	FVector GetSkeletalMeshRightVector();

	// Called to get the skeletal mesh rotation as it depends on how this mesh was exported
	UFUNCTION(BlueprintNativeEvent, Category = "CharacterPawn Directions")
	FRotator GetSkeletalMeshRotation();

	// Called to set isInAir on the animation blueprint
	UFUNCTION(BlueprintNativeEvent, Category = "CharacterPawn Animations")
	bool SetAnimBlueprintIsInAir();

public:
	// Get Muzzle Location (depends on CharacterPawn Muzzle properties)
	FVector GetMuzzleLocation();

	// Get Forward vector using pawn direction and camera Z
	FVector GetForwardVector();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Sets rotation of the 3PS pawn
	void Set3psRotation(float deltaX, float deltaY);

	// Sets rotation of the FPS pawn
	void SetFpsRotation(float deltaX, float deltaY);

	// Sets forward/backward location of pawn
	void SetMoveForward(float value);

	// Sets sideways location of pawn
	void SetMoveSideways(float value);

	// Sets if pawn is running
	void SetIsRunning(bool value);

	// Sets if pawn is jumping from CharacterController or to signal to stop jumping from Anim BP
	UFUNCTION(BlueprintCallable, Category = "CharacterPawn Animations")
	void SetIsJumping(bool value);

};
