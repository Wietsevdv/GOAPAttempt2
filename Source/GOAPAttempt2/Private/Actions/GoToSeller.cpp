// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/GoToSeller.h"
#include "Kismet/GameplayStatics.h"

#include "GOAPController.h"
#include "Seller.h"

#include "Navigation/PathFollowingComponent.h"

void UGoToSeller::Execute(TObjectPtr<AGOAPController> AgentController, bool& bActionFinished, float DeltaTime)
{
	if (!Started)
	{
		Seller = Cast<ASeller>(UGameplayStatics::GetActorOfClass(this, TSubclassOf<ASeller>()));

		if (Seller)
		{
			if (AgentController->MoveToActor(Seller, 3.f) == EPathFollowingRequestResult::Failed && GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, "GoToSeller could not get a path to follow");
			}
		}

		Started = true;
	}


}
