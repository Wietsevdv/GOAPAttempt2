// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/SellWood.h"
#include "Kismet/GameplayStatics.h"

#include "GOAPController.h"
#include "Seller.h"

void USellWood::Execute(TObjectPtr<AGOAPAgent> Agent, TObjectPtr<AGOAPController> AgentController, bool& bActionFinished, float DeltaTime)
{
	if (!Started)
	{
		Seller = Cast<ASeller>(UGameplayStatics::GetActorOfClass(this, TSubclassOf<ASeller>()));

		Started = true;
	}

	Timer += DeltaTime;
	if (Timer >= 2.f)
	{
		Started = false;

		Timer = 0.f;
		Seller = nullptr;

		bActionFinished = true;
	}
}
