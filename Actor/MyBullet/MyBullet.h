// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyBullet.generated.h"

UCLASS()
class LEARNINGKITPROJECT_API AMyBullet : public AActor {
	
	GENERATED_BODY()
	
public:	

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* VisualMesh;

	// Specifies the damage value of the bullet
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Bullet")
	float BulletDamage;

	// Specifies how long the bullet lives in the world in seconds
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Bullet")
	float BulletEol;

	// Specifies the type of bullet (1 = light, 2 = heavy)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Bullet")
	float BulletType;

	// Specifies the force multiplier for the bullet in direction of shot
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Bullet")
	float BulletForceMultiplier;

	// Specifies the size multiplier on 0.1 scale of shape_sphere
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "My Bullet")
	float BulletSizeMultiplier;

	// Sets default values for this actor's properties
	AMyBullet();

	// Exposes method to add force
	void AddCustomForce(FVector force);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
