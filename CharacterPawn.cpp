// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterPawn.h"

// Sets default values
ACharacterPawn::ACharacterPawn() {
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ACharacterPawn::BeginPlay() {
	Super::BeginPlay();
}

// Called every frame
void ACharacterPawn::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ACharacterPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ACharacterPawn::SetRotation(FRotator Rotation) {
	SetActorRotation(Rotation);
}
