// Fill out your copyright notice in the Description page of Project Settings.


#include "Actions/ChopTree.h"
#include "Kismet/GameplayStatics.h"

#include "GOAPAgent.h"
#include "GOAPController.h"
#include "Tree.h"

void UChopTree::Execute(TObjectPtr<AGOAPAgent> Agent, TObjectPtr<AGOAPController> AgentController, bool& bActionFinished, float DeltaTime)
{
	if (!Started)
	{
		//start animation

		Tree = Cast<ATree>(UGameplayStatics::GetActorOfClass(this, TSubclassOf<ATree>(ATree::StaticClass())));
		Agent->SetIsChoppingTree(true);
	}

	//repeat chopping if its a singular chop
	
	//either damage tree with each chop, 
	// or a number of chops 
	// or a timer
	Timer += DeltaTime;
	if (Timer >= 5.f)
	{
		Started = false;

		Timer = 0.f;
		Tree = nullptr;
		Agent->SetIsChoppingTree(false);
		Agent->DestroyAxe();

		bActionFinished = true;
	}
}
