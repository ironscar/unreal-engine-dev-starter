#include "TimerTest.h"

// Sets default values
ATimerTest::ATimerTest() {
	// Set this actor to call Tick() every frame. You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ATimerTest::BeginPlay() {
	Super::BeginPlay();

	// register timer component
	Timer = NewObject<UTimer>(this);
	check(Timer != nullptr);
	Timer->RegisterComponent();

	// start timer and save start time
	timerCounts = 0;
	Timer->SetDuration(3.0f);
	Timer->Start();
	StartTime = FDateTime::Now();
}

// Called every frame
void ATimerTest::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	if (Timer->IsFinished() && timerCounts < 10) {
		timerCounts++;
		UE_LOG(LogTemp, Warning, TEXT("Timer Test : Finished after %f seconds!"), (FDateTime::Now() - StartTime).GetTotalSeconds());

		Timer->Start();
		StartTime = FDateTime::Now();
	}
}
