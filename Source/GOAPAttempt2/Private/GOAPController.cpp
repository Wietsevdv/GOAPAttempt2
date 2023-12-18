// Fill out your copyright notice in the Description page of Project Settings.


#include "GOAPController.h"
#include "GOAPBrainComponent.h"
#include "GOAPCharacter.h"

AGOAPController::AGOAPController() :
	Super(),
	DReachedGoTo{}
{
	BrainComponent = CreateDefaultSubobject<UGOAPBrainComponent>("Brain");
	GOAPBrain = Cast<UGOAPBrainComponent>(BrainComponent);
}

void AGOAPController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	DReachedGoTo.ExecuteIfBound();
}

void AGOAPController::BeginPlay()
{
	Super::BeginPlay();

	if (auto Temp = Cast<AGOAPCharacter>(GetPawn()))
	{
		GOAPAgent = Temp;
	}
}
