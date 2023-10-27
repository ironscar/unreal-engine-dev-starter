// Fill out your copyright notice in the Description page of Project Settings.

#include "MyBullet.h"

// Sets default values
AMyBullet::AMyBullet() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	VisualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	VisualMesh->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere"));
	
	if (SphereVisualAsset.Succeeded()) {
		VisualMesh->SetStaticMesh(SphereVisualAsset.Object);
		VisualMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
		SetRootComponent(VisualMesh);
	}
}

// Called when the game starts or when spawned
void AMyBullet::BeginPlay() {
	Super::BeginPlay();

	// set size of bullet, simulate physics true and enable gravity false
	VisualMesh->SetRelativeScale3D(FVector(0.1f, 0.1f, 0.1f) * BulletSizeMultiplier);
	VisualMesh->SetSimulatePhysics(true);
	VisualMesh->SetEnableGravity(false);

	// set life span of Eol seconds
	SetLifeSpan(BulletEol);
}

void AMyBullet::AddCustomForce(FVector ForwardVector) {
	FVector ForceVector = ForwardVector * BulletForceMultiplier;
	VisualMesh->AddImpulse(ForceVector);
}
