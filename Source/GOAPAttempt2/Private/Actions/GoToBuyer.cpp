// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/GoToBuyer.h"

void UGoToBuyer::Execute(TObjectPtr<AGOAPController> AgentController, bool& bActionFinished, float DeltaTime) const
{
	if (GEngine && AgentController)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Cyan, "Going To Buyer");
		bActionFinished = true;
	}
}
