// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Timer.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LEARNINGKITPROJECT_API UTimer : public UActorComponent {

	GENERATED_BODY()

	private:
		bool bRunning = false;
		bool bStarted = false;
		float ElapsedSeconds = 0;
		float TotalSeconds = 0;

	public:	
		// Sets default values for this component's properties
		UTimer();

	protected:
		// Called when the game starts
		virtual void BeginPlay() override;

	public:	
		// Called every frame
		virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		// Tells whether timer is finished or not
		bool IsFinished();

		// Tells whether timer is running or not
		bool IsRunning();

		// Sets duration of the timer
		void SetDuration(float Duration);

		// Starts the timer
		void Start();

};
