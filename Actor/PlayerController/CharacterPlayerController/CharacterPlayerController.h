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
 */
UCLASS()
class LEARNINGKITPROJECT_API ACharacterPlayerController : public APlayerController {

	GENERATED_BODY()

public:
	
	// specifies if camera is FPS or 3PS
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterPlayerController")
	bool IsFPS = true;

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
	void ChangeAmmo();

protected:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	class UInputMappingContext* InputMapping;

	// for looking around
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	UInputAction* Look2D;

	// to shoot
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	UInputAction* MouseLeft;

	// to toggle ammo
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
	UInputAction* MouseRight;

private:

	// pawn reference
	ACharacterPawn* CharacterPawn;

	// enhanced input component reference
	UEnhancedInputComponent* PlayerEnhancedInputComponent;

	// selected ammo type (1 for light and 2 for heavy)
	float SelectedAmmoType = 1;

};
