// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/GoToBuyer.h"
#include "Kismet/GameplayStatics.h"

#include "GOAPController.h"
#include "Buyer.h"

#include "Navigation/PathFollowingComponent.h"

void UGoToBuyer::Execute(TObjectPtr<AGOAPAgent> Agent, TObjectPtr<AGOAPController> AgentController, bool& bActionFinished, float DeltaTime)
{
	if (!Started)
	{
		if (Buyer = Cast<ABuyer>(UGameplayStatics::GetActorOfClass(this, TSubclassOf<ABuyer>(ABuyer::StaticClass()))))
		{
			const auto RequestResult = AgentController->MoveToActor(Buyer, 3.f);

			if (RequestResult == EPathFollowingRequestResult::Failed && GEngine)
				GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, "GoToBuyer could not get a path to follow");
			else
				AgentController->GetReachedGoToDelegate().BindUObject(this, &UGoToBuyer::SetHasReached);
		}

		Started = true;
		return;
	}

	if (bHasReached)
	{
		Started = false;

		Buyer = nullptr;

		bHasReached = false;
		AgentController->GetReachedGoToDelegate().Unbind();

		bActionFinished = true;
	}
}
