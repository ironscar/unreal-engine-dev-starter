// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GameplayStatics.h"

#include "MyDestroyerGameMode.h"

void AMyDestroyerGameMode::StartDestroyTimer() {
	FTimerHandle Timer;
	GetWorldTimerManager().SetTimer(Timer, this, &AMyDestroyerGameMode::DestroyDestructible, TimeDuration);
}

void AMyDestroyerGameMode::DestroyDestructible() {
	
	TArray<AActor*> TaggedActors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), "Destructible", TaggedActors);

	if (TaggedActors.Num() > 0) {
		TaggedActors[0]->Destroy();

		UE_LOG(LogTemp, Warning, TEXT("Destroyed by game mode"));
	} else {
		UE_LOG(LogTemp, Warning, TEXT("No actors to destroy"));
	}

	StartDestroyTimer();
}

void AMyDestroyerGameMode::BeginPlay() {
	Super::BeginPlay();

	StartDestroyTimer();
}
