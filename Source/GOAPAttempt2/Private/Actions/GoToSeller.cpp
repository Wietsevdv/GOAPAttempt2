// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/GoToSeller.h"
#include "Kismet/GameplayStatics.h"

#include "GOAPController.h"
#include "Seller.h"

#include "Navigation/PathFollowingComponent.h"

void UGoToSeller::Execute(TObjectPtr<AGOAPAgent> Agent, TObjectPtr<AGOAPController> AgentController, bool& bActionFinished, float DeltaTime)
{
	if (!Started)
	{
		if (Seller = Cast<ASeller>(UGameplayStatics::GetActorOfClass(this, TSubclassOf<ASeller>(ASeller::StaticClass()))))
		{
			const auto RequestResult = AgentController->MoveToActor(Seller, 3.f);

			if (RequestResult == EPathFollowingRequestResult::Failed && GEngine)
				GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, "GoToBuyer could not get a path to follow");
			else
				AgentController->GetReachedGoToDelegate().BindUObject(this, &UGoToSeller::SetHasReached);
		}

		Started = true;
	}

	if (bHasReached)
	{
		Started = false;
	
		Seller = nullptr;

		bHasReached = false;
		AgentController->GetReachedGoToDelegate().Unbind();

		bActionFinished = true;
	}
}
