// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/BuyAxe.h"
#include "Kismet/GameplayStatics.h"

#include "GOAPAgent.h"
#include "GOAPController.h"
#include "Seller.h"
#include "Axe.h"

void UBuyAxe::Execute(TObjectPtr<AGOAPAgent> Agent, TObjectPtr<AGOAPController> AgentController, bool& bActionFinished, float DeltaTime)
{
	if (!Started)
	{
		if (Seller = Cast<ASeller>(UGameplayStatics::GetActorOfClass(this, TSubclassOf<ASeller>(ASeller::StaticClass()))))
		{
			if (TObjectPtr<AAxe> Axe{ Seller->SellAxe() })
			{
				Agent->SetAxe(Axe);

				Started = false;

				Timer = 0.f;
				Seller = nullptr;

				bActionFinished = true;
			}
		}
	}
}
