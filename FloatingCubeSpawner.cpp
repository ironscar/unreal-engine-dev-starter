// Fill out your copyright notice in the Description page of Project Settings.

#include "FloatingCubeSpawner.h"

// Sets default values
AFloatingCubeSpawner::AFloatingCubeSpawner() {
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AFloatingCubeSpawner::BeginPlay() {
	Super::BeginPlay();

	StartSpawnTimer();
}

// Called every frame
void AFloatingCubeSpawner::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

void AFloatingCubeSpawner::SpawnFloatingActor() {

	// select which floating actor to spawn
	TSubclassOf<AMyFloatingActor> SpawnFloatingActor;
	int FloatingActorIndex = FMath::RandRange(0, 1);
	if (FloatingActorIndex == 1) {
		SpawnFloatingActor = UMyFloatingActor1;
	} else {
		SpawnFloatingActor = UMyFloatingActor2;
	}

	// set spawn location randomly between defined limits
	FVector SpawnLocation = FVector(
		FMath::RandRange(MinSpawnX, MaxSpawnX),
		FMath::RandRange(MinSpawnY, MaxSpawnY),
		FMath::RandRange(MinSpawnZ, MaxSpawnZ)
	);

	// spawn the actual floating actor asset
	GetWorld()->SpawnActor<AMyFloatingActor>(SpawnFloatingActor, SpawnLocation, FRotator::ZeroRotator);

	// start spawn timer again
	StartSpawnTimer();
}

void AFloatingCubeSpawner::StartSpawnTimer() {
	float TimerDuration = firstSpawn ? 1 : FMath::RandRange(MinSpawnDelaySeconds, MaxSpawnDelaySeconds);
	firstSpawn = false;
	FTimerHandle Timer;
	GetWorldTimerManager().SetTimer(Timer, this, &AFloatingCubeSpawner::SpawnFloatingActor, TimerDuration);
}
