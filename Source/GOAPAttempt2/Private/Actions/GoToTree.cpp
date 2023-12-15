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
		Tree = Cast<ATree>(UGameplayStatics::GetActorOfClass(this, TSubclassOf<ATree>()));

		if (Tree)
		{
			if (AgentController->MoveToActor(Tree, 3.f) == EPathFollowingRequestResult::Type::Failed && GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, "GoToTree could not get a path to follow");
			}
		}

		Started = true;
	}
	
	AgentController->GetPathFollowingComponent()->HasReached(Tree, EPathFollowingReachMode::ExactLocation);

	if (AgentController->GetPawn()->GetDistanceTo(Tree) )
}
