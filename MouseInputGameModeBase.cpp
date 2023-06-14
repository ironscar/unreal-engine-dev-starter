// Fill out your copyright notice in the Description page of Project Settings.


#include "MouseInputGameModeBase.h"

AMouseInputGameModeBase::AMouseInputGameModeBase() {
	// set pawn
	ConstructorHelpers::FObjectFinder<UClass> PawnClass(TEXT("Class'/Game/LearningKit_Games/Blueprints/MyClasses/BP_MyCharacterPawn.BP_MyCharacterPawn_C'"));
	DefaultPawnClass = PawnClass.Object != nullptr ? PawnClass.Object : nullptr;

	// set player controller
	ConstructorHelpers::FObjectFinder<UClass> ControllerClass(TEXT("Class'/Game/LearningKit_Games/Blueprints/MyClasses/BP_MyCharacterPlayerController.BP_MyCharacterPlayerController_C'"));
	PlayerControllerClass = ControllerClass.Object != nullptr ? ControllerClass.Object : nullptr;
}
