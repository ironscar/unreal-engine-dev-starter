// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LearningKitProject/Actor/MyFloatingActor/MyFloatingActor.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FloatingCubeSpawner.generated.h"

/**
 * An actor that spawns FloatingActors (its subclass BPs) using a timer at regular intervals
 */
UCLASS()
class LEARNINGKITPROJECT_API AFloatingCubeSpawner : public AActor {

	GENERATED_BODY()

private:
	// spawn delay support
	bool firstSpawn = true;
	const float MinSpawnDelaySeconds = 5;
	const float MaxSpawnDelaySeconds = 10;

	// spawn location support
	const float MinSpawnX = -800;
	const float MaxSpawnX = -600;
	const float MinSpawnY = -200;
	const float MaxSpawnY = 200;
	const float MinSpawnZ = 150;
	const float MaxSpawnZ = 200;

	// start spawn timer
	void StartSpawnTimer();
	
public:	
	UPROPERTY(EditAnywhere, meta = (MetaClass = "MyFloatingActor"), Category = FloatingActorBlueprints)
	TSubclassOf<AMyFloatingActor> UMyFloatingActor1;

	UPROPERTY(EditAnywhere, meta = (MetaClass = "MyFloatingActor"), Category = FloatingActorBlueprints)
	TSubclassOf<AMyFloatingActor> UMyFloatingActor2;

	// Spawns a floating cube
	UFUNCTION()
	void SpawnFloatingActor();

	// Sets default values for this actor's properties
	AFloatingCubeSpawner();

protected:
	// Called when the game starts or when spawned 
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
