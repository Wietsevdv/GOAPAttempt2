// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/GoToTree.h"
#include "Kismet/GameplayStatics.h"

#include "GOAPController.h"
#include "Tree.h"

#include "Navigation/PathFollowingComponent.h"

void UGoToTree::Execute(TObjectPtr<AGOAPController> AgentController, bool& bActionFinished, float DeltaTime)
{
	if (!Started)
	{
		if (Tree = Cast<ATree>(UGameplayStatics::GetActorOfClass(this, TSubclassOf<ATree>(ATree::StaticClass()))))
		{
			const auto RequestResult = AgentController->MoveToActor(Tree, 100.f);

			if (RequestResult == EPathFollowingRequestResult::Failed && GEngine)
				GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, "GoToBuyer could not get a path to follow");
			else
				AgentController->GetReachedGoToDelegate().BindUObject(this, &UGoToTree::SetHasReached);
		}

		Started = true;
	}
	
	if (bHasReached)
	{		
		Started = false;

		Tree = nullptr;

		bHasReached = false;
		AgentController->GetReachedGoToDelegate().Unbind();

		bActionFinished = true;
	}
}
