// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LearningKitProject/Actor/MyBullet/MyBullet.h"
#include "LearningKitProject/Actor/Pawn/CharacterPawn/CharacterPawn.h"

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/PlayerController.h"
#include "CharacterPlayerController.generated.h"

/**
 * A character player controller to use with the character pawn
 * Assumptions:
 *	- Will be inherited by a Blueprint class
 *  - BP class must set an InputMappingContext for all the different EnhancedInput bindings
 *  - BP class must also set all the individual EnhancedInputActions which are already in the context
 *  - BP class must set the blueprints used for light ammo and heavy ammo
 *	- BP class also allows overridding the behavior based on FPS or 3PS
 *	- Controls pawns which are derived from CharacterPawn
 *	- Override the DefaultPlayerController class in Project settings > Maps & Modes > Default modes > Selected game mode to a derivative of this class to use it
 */
UCLASS()
class LEARNINGKITPROJECT_API ACharacterPlayerController : public APlayerController {

	GENERATED_BODY()

public:
	
	// specifies if camera is FPS or 3PS
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterPlayerController")
	bool IsFPS = false;

	// specifies the light ammo type
	UPROPERTY(EditAnywhere, meta = (MetaClass = "MyBullet"), Category = MyBulletBlueprints)
	TSubclassOf<AMyBullet> LightAmmo;

	// specifies the heavy ammo type
	UPROPERTY(EditAnywhere, meta = (MetaClass = "MyBullet"), Category = MyBulletBlueprints)
	TSubclassOf<AMyBullet> HeavyAmmo;

	// called at start of play or on spawn
	virtual void BeginPlay() override;

	// called every frame and delta time is the time elasped since last frame
	virtual void PlayerTick(float DeltaTime) override;

	// called to bind functionality to input
	virtual void SetupInputComponent() override;

	// called when mouse moved
	void Look(const FInputActionValue& Value);

	// called when mouse left is clicked
	void Shoot();

	// called when mouse right is clicked
	void ChangeAmmo(float value);

	// called when W/S on keyboard is pressed
	void MoveForward(const FInputActionValue& Value);

	// called when A/D on keyboard is pressed
	void MoveSideways(const FInputActionValue& Value);

	// called when Left Shift is Started or Completed
	void SetIsRunning(const FInputActionValue& Value);

protected:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	class UInputMappingContext* InputMapping;

	// for looking around
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	UInputAction* Look2D;

	// to shoot
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	UInputAction* MouseLeft;

	// to focus
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	UInputAction* MouseRight;

	// to move forward
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	UInputAction* MoveY;

	// to move sideways
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	UInputAction* MoveX;

	// to select weapon 1
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	UInputAction* Weapon1Select;

	// to select weapon 2
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	UInputAction* Weapon2Select;

	// to run
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	UInputAction* Run;

private:

	// pawn reference
	ACharacterPawn* CharacterPawn;

	// parameterized delegate for input binding
	DECLARE_DELEGATE_OneParam(FWeaponSelectDelegate, const float);

	// enhanced input component reference
	UEnhancedInputComponent* PlayerEnhancedInputComponent;

	// selected ammo type (1 for light and 2 for heavy)
	float SelectedAmmoType = 1;

};
