// Fill out your copyright notice in the Description page of Project Settings.


#include "GOAPController.h"
#include "GOAPBrainComponent.h"
#include "GOAPAgent.h"

AGOAPController::AGOAPController() :
	Super(),
	DReachedGoTo{}
{
	BrainComponent = CreateDefaultSubobject<UGOAPBrainComponent>("Brain");
	GOAPBrain = Cast<UGOAPBrainComponent>(BrainComponent);
}

AGOAPAgent* AGOAPController::GetGOAPAgent()
{
	return GOAPAgent;
}

void AGOAPController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	DReachedGoTo.ExecuteIfBound();
}

void AGOAPController::BeginPlay()
{
	Super::BeginPlay();

	if (auto Temp = Cast<AGOAPAgent>(GetPawn()))
	{
		GOAPAgent = Temp;
	}
}
