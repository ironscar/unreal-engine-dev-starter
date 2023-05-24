// Fill out your copyright notice in the Description page of Project Settings.

#include "Timer.h"

// Sets default values for this component's properties
UTimer::UTimer() {
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}

// Called when the game starts
void UTimer::BeginPlay() {
	Super::BeginPlay();
	
}

// Called every frame
void UTimer::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// update timer and check for finished
	if (bRunning) {
		ElapsedSeconds += DeltaTime;

		if (ElapsedSeconds >= TotalSeconds) {
			bRunning = false;
		}
	}
}

bool UTimer::IsFinished() {
	return bStarted && !bRunning;
}

bool UTimer::IsRunning() {
	return bRunning;
}

void UTimer::SetDuration(float Duration) {
	if (!bRunning && Duration > 0) {
		TotalSeconds = Duration;
	}
}

void UTimer::Start() {
	if ((!bStarted || !bRunning) && TotalSeconds > 0) {
		bStarted = true;
		bRunning = true;
		ElapsedSeconds = 0;
	}
}
