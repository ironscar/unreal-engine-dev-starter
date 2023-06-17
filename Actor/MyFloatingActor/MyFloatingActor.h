// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyFloatingActor.generated.h"

/**
 * An actor that is a cube with the 'Destructible' tag that levitates and rotates, and gets destroyed after 20 seconds
 */
UCLASS()
class LEARNINGKITPROJECT_API AMyFloatingActor : public AActor {

	GENERATED_BODY()
	
	public:
		// Sets default values for this actor's properties
		AMyFloatingActor();

		UPROPERTY(VisibleAnywhere)
			UStaticMeshComponent* VisualMesh;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyFloatingActor")
			float FloatSpeed = 50.0f;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyFloatingActor")
			float RotationSpeed = 50.0f;

	protected:
		// Called when the game starts or when spawned
		virtual void BeginPlay() override;

	public:
		// Called every frame
		virtual void Tick(float DeltaTime) override;

};
