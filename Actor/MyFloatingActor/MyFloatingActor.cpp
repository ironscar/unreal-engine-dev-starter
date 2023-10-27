// Fill out your copyright notice in the Description page of Project Settings.

#include "MyFloatingActor.h"

// Sets default values
AMyFloatingActor::AMyFloatingActor() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	VisualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	VisualMesh->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube"));

	if (CubeVisualAsset.Succeeded()) {
		VisualMesh->SetStaticMesh(CubeVisualAsset.Object);
		VisualMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
		VisualMesh->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));
		SetRootComponent(VisualMesh);

		// add the destructibe tag that was custom added to all floating actors during spawn (will not be visible in editor if BPs created from it)
		this->Tags.Add(FName("Destructible"));
	}
}

// Called when the game starts or when spawned
void AMyFloatingActor::BeginPlay() {
	Super::BeginPlay();

	// destroy floating cube after 20 seconds
	SetLifeSpan(20);
}

// Called every frame
void AMyFloatingActor::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	FVector NewLocation = GetActorLocation();
	FRotator NewRotation = GetActorRotation();
	float RunningTime = GetGameTimeSinceCreation();
	float DeltaHeight = 2 * (FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime));

	// Scale height factor by FloatSpeed
	NewLocation.Z += DeltaHeight * FloatSpeed;

	// Rotate at RotationSpeed degrees per second
	NewRotation.Yaw += DeltaTime * RotationSpeed;

	SetActorLocationAndRotation(NewLocation, NewRotation);
}
