// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/GoToBuyer.h"
#include "Kismet/GameplayStatics.h"

#include "GOAPController.h"
#include "Buyer.h"

#include "Navigation/PathFollowingComponent.h"

void UGoToBuyer::Execute(TObjectPtr<AGOAPController> AgentController, bool& bActionFinished, float DeltaTime)
{
	if (!Started)
	{
		Buyer = Cast<ABuyer>(UGameplayStatics::GetActorOfClass(this, TSubclassOf<ABuyer>()));

		if (Buyer)
		{
			if (AgentController->MoveToActor(Buyer, 3.f) == EPathFollowingRequestResult::Failed && GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, "GoToBuyer could not get a path to follow");
			}
		}

		Started = true;
	}


}
