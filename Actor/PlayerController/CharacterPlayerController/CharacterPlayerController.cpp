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
	PlayerEnhancedInputComponent->BindAction(Weapon1Select, ETriggerEvent::Completed, this, &ACharacterPlayerController::ChangeAmmo, 1.0f);
	PlayerEnhancedInputComponent->BindAction(Weapon2Select, ETriggerEvent::Completed, this, &ACharacterPlayerController::ChangeAmmo, 2.0f);
	PlayerEnhancedInputComponent->BindAction(Look2D, ETriggerEvent::Triggered, this, &ACharacterPlayerController::Look);

	PlayerEnhancedInputComponent->BindAction(Run, ETriggerEvent::Started, this, &ACharacterPlayerController::SetIsRunning);
	PlayerEnhancedInputComponent->BindAction(Run, ETriggerEvent::Completed, this, &ACharacterPlayerController::SetIsRunning);

	PlayerEnhancedInputComponent->BindAction(MoveY, ETriggerEvent::Triggered, this, &ACharacterPlayerController::MoveForward);
	PlayerEnhancedInputComponent->BindAction(MoveY, ETriggerEvent::Completed, this, &ACharacterPlayerController::MoveForward);
	PlayerEnhancedInputComponent->BindAction(MoveX, ETriggerEvent::Triggered, this, &ACharacterPlayerController::MoveSideways);
	PlayerEnhancedInputComponent->BindAction(MoveX, ETriggerEvent::Completed, this, &ACharacterPlayerController::MoveSideways);
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

void ACharacterPlayerController::ChangeAmmo(float value) {
	// select weapon type
	SelectedAmmoType = value;
}

void ACharacterPlayerController::MoveForward(const FInputActionValue& Value) {
	const float DirectionValue = Value.Get<float>();
	if (CharacterPawn != nullptr) {
		// same for both FPS and 3PS
		CharacterPawn->SetMoveForward(DirectionValue);
	}
}

void ACharacterPlayerController::MoveSideways(const FInputActionValue& Value) {
	const float DirectionValue = Value.Get<float>();
	if (CharacterPawn != nullptr) {
		CharacterPawn->SetMoveSideways(DirectionValue);
	}
}

void ACharacterPlayerController::SetIsRunning(const FInputActionValue& Value) {
	CharacterPawn->SetIsRunning(Value.Get<bool>());
}
