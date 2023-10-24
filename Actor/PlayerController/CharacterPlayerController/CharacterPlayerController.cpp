// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterPlayerController.h"

void ACharacterPlayerController::BeginPlay() {
	Super::BeginPlay();

	CharacterPawn = (ACharacterPawn*)GetPawn();
}

void ACharacterPlayerController::PlayerTick(float DeltaTime) {
	Super::PlayerTick(DeltaTime);

	// use mouse movement to rotate
	if (CharacterPawn != nullptr) {
		float deltaX;
		float deltaY;
		this->GetInputMouseDelta(deltaX, deltaY);
		if (IsFPS) {
			CharacterPawn->SetFpsRotation(deltaX, deltaY);
		} else {
			CharacterPawn->Set3psRotation(deltaX, deltaY);
		}
	}
}

void ACharacterPlayerController::SetupInputComponent() {
	Super::SetupInputComponent();

	check(InputComponent != nullptr);

	// shoot binding
	InputComponent->BindAction(
		"Shoot", EInputEvent::IE_Pressed, this, &ACharacterPlayerController::Shoot);

	// change ammo binding
	InputComponent->BindAction(
		"ChangeAmmo", EInputEvent::IE_Pressed, this, &ACharacterPlayerController::ChangeAmmo);
}

void ACharacterPlayerController::Shoot() {
	// spawn a bullet actor
	TSubclassOf<AMyBullet> SelectedAmmo = SelectedAmmoType == 1 ? LightAmmo : HeavyAmmo;
	if (SelectedAmmo != nullptr) {
		// get muzzle location and spawn bullet
		FVector BulletSpawnLocation = CharacterPawn->GetMuzzleLocation();
		AMyBullet* Bullet = GetWorld()->SpawnActor<AMyBullet>(SelectedAmmo, BulletSpawnLocation, FRotator::ZeroRotator);

		// get forward vector and add impulse
		FVector ForwardVector = CharacterPawn->GetActorForwardVector();
		Bullet->AddCustomForce(ForwardVector);
	}
}

void ACharacterPlayerController::ChangeAmmo() {
	// change the type of ball actor to be spawned
	SelectedAmmoType = SelectedAmmoType == 1 ? 2 : 1;
}
