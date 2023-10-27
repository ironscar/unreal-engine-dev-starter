// Fill out your copyright notice in the Description page of Project Settings.

#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "CharacterPlayerController.h"

void ACharacterPlayerController::BeginPlay() {
	Super::BeginPlay();

	CharacterPawn = (ACharacterPawn*)GetPawn();
}

void ACharacterPlayerController::PlayerTick(float DeltaTime) {
	Super::PlayerTick(DeltaTime);
}

void ACharacterPlayerController::SetupInputComponent() {
	Super::SetupInputComponent();
	check(InputComponent != nullptr);

	// setup enhanced input component
	UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	SubSystem->ClearAllMappings();
	SubSystem->AddMappingContext(InputMapping, 0);
	PlayerEnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);

	// bind enhanced input actions
	PlayerEnhancedInputComponent->BindAction(MouseLeft, ETriggerEvent::Completed, this, &ACharacterPlayerController::Shoot);
	PlayerEnhancedInputComponent->BindAction(MouseRight, ETriggerEvent::Completed, this, &ACharacterPlayerController::ChangeAmmo);
	PlayerEnhancedInputComponent->BindAction(Look2D, ETriggerEvent::Triggered, this, &ACharacterPlayerController::Look);
}

void ACharacterPlayerController::Look(const FInputActionValue& Value) {
	// use mouse movement to rotate
	const FVector2D LookValue = Value.Get<FVector2D>();
	if (CharacterPawn != nullptr && !LookValue.IsZero()) {
		float deltaX = LookValue.X;
		float deltaY = LookValue.Y;
		if (IsFPS) {
			CharacterPawn->SetFpsRotation(deltaX, deltaY);
		} else {
			CharacterPawn->Set3psRotation(deltaX, deltaY);
		}
	}
}

void ACharacterPlayerController::Shoot() {
	// spawn a bullet actor
	TSubclassOf<AMyBullet> SelectedAmmo = SelectedAmmoType == 1 ? LightAmmo : HeavyAmmo;
	if (SelectedAmmo != nullptr) {
		// get muzzle location and spawn bullet
		FVector BulletSpawnLocation = CharacterPawn->GetMuzzleLocation();
		AMyBullet* Bullet = GetWorld()->SpawnActor<AMyBullet>(SelectedAmmo, BulletSpawnLocation, FRotator::ZeroRotator);

		// get forward vector and add impulse
		FVector ForwardVector = CharacterPawn->GetForwardVector();
		Bullet->AddCustomForce(ForwardVector);
	}
}

void ACharacterPlayerController::ChangeAmmo() {
	// change the type of ball actor to be spawned
	SelectedAmmoType = SelectedAmmoType == 1 ? 2 : 1;
}
