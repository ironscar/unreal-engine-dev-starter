// Fill out your copyright notice in the Description page of Project Settings.


#include "PrintMessage.h"

// Sets default values
APrintMessage::APrintMessage() {
 	// Set this actor to call Tick() every frame if true.  
	// You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void APrintMessage::BeginPlay() {
	Super::BeginPlay();

	// some random calculations
	float Angle = 45.0;
	Angle *= 3.1416 / 180;
	Angle += 1;

	// prints the following message in the output log at begin play
	UE_LOG(LogTemp, Warning, TEXT("Hello World! %f"), Angle);
}

// Called every frame
void APrintMessage::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}
