// Fill out your copyright notice in the Description page of Project Settings.


#include "GOAPController.h"
#include "GOAPBrainComponent.h"
#include "GOAPCharacter.h"

AGOAPController::AGOAPController()
{
	BrainComponent = CreateDefaultSubobject<UGOAPBrainComponent>("Brain");
	GOAPBrain = Cast<UGOAPBrainComponent>(BrainComponent);
}

void AGOAPController::BeginPlay()
{
	if (auto Temp = Cast<AGOAPCharacter>(GetPawn()))
	{
		GOAPAgent = Temp;
	}
}
