// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/DrinkWater.h"

void UDrinkWater::Execute(TObjectPtr<AGOAPAgent> Agent, TObjectPtr<AGOAPController> AgentController, bool& bActionFinished, float DeltaTime)
{
	if (GEngine && AgentController)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Cyan, "Drinking Water");
		bActionFinished = true;
	}
}
