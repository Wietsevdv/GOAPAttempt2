// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/EatFood.h"

void UEatFood::Execute(TObjectPtr<AGOAPAgent> Agent, TObjectPtr<AGOAPController> AgentController, bool& bActionFinished, float DeltaTime)
{
	if (GEngine && AgentController)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Cyan, "Eating Food");
		bActionFinished = true;
	}
}
