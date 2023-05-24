#pragma once

#include "Timer.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TimerTest.generated.h"

UCLASS()
class LEARNINGKITPROJECT_API ATimerTest : public AActor {
	
	GENERATED_BODY()

	private:
		UTimer* Timer;
		FDateTime StartTime;
		int timerCounts;
	
	public:
		// Sets default values for this actor's properties
		ATimerTest();

	protected:
		// Called when the game starts or when spawned
		virtual void BeginPlay() override;

	public:
		// Called every frame
		virtual void Tick(float DeltaTime) override;

};
