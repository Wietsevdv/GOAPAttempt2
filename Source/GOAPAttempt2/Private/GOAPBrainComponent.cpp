// Fill out your copyright notice in the Description page of Project Settings.


#include "GOAPBrainComponent.h"

#include <algorithm>

#include "Actions/ChopTree.h"
#include "Actions/SellWood.h"
#include "Actions/EatFood.h"
#include "Actions/DrinkWater.h"

#include "Actions/GoToTree.h"
#include "Actions/GoToSeller.h"
#include "Actions/GoToBuyer.h"

UGOAPBrainComponent::UGOAPBrainComponent() :
	Super(),
	CurrentGoal{}
{
	SetWorldStates();
	SetActions();
	SetGoals();
}

void UGOAPBrainComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UGOAPBrainComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	Goal NewGoal{};
	DecideGoal(NewGoal);

	if (CurrentGoal != NewGoal)
	{
		CurrentGoal = NewGoal;
		ClearChain();
		CreateChain();
	}
	else if (ActionChain.empty())
	{
		CreateChain();
		//just update current chain (could be that this chain is fully executed. In that case also make a new chain. Don't just restart)
	}
}









void UGOAPBrainComponent::DecideGoal(Goal& NewGoal) const
{
	for (const Goal& Goal : Goals)
	{
		const bool* State = WorldStates.Find(Goal.first.first);
		if (State && *State == Goal.first.second)
		{
			NewGoal = Goal;
			return;
		}

		if (State == nullptr)
			PrintDebug(DebugMessage::WorldStateNotFound);
	}
}

void UGOAPBrainComponent::CreateChain()
{
	if (!ChainActionFor(CurrentGoal.second))
	{
		PrintDebug(DebugMessage::FailedToCreateChainForGoal);
	}

	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green, "Chain Created");
}

bool UGOAPBrainComponent::ChainActionFor(const DesiredState& DS)
{
	//get actions that effect the desired WS
	auto PossibleActionsP = Actions.Find(DS.first);
	auto& PossibleActions = *PossibleActionsP;
	if (PossibleActionsP && PossibleActions.Num())
	{
		//for now let's just take the first action.
		//check if its effect on the WS is the desired one
		auto PossibleAction = PossibleActions[0].Get();
		const auto& PAConsequences = PossibleAction->GetConsequences();
		if (PAConsequences.Find(DS) >= 0)
		{
			//this action has the desired consequence. Now check its PC and find actions to satisfy them before adding this action
			const auto& PAPreconditions = PossibleAction->GetPreconditions();
			for (auto& PAPrecondition : PAPreconditions)
			{
				if (!ChainActionFor(PAPrecondition))
				{
					PrintDebug(DebugMessage::CannotSatisfyPrecondition);
					return false;
				}
			}

			ActionChain.emplace(PossibleAction);
			return true;
		}
		else
		{
			PrintDebug(DebugMessage::NoActionForDesiredState);
		}
	}
	else
		PrintDebug(DebugMessage::NoActionForDesiredState);

	return false;
}

void UGOAPBrainComponent::ClearChain()
{
	if (!ActionChain.empty())
	{
		for (size_t i{}; i < ActionChain.size(); ++i)
		{
			ActionChain.pop();
		}
	}
}

//----------CONSTRUCTION----------
//
void UGOAPBrainComponent::SetWorldStates()
{
	//statuses
	WorldStates.Emplace(WorldState::IsInDanger, false);
	WorldStates.Emplace(WorldState::IsDamaged, false);
	WorldStates.Emplace(WorldState::IsThirsty, false);
	WorldStates.Emplace(WorldState::IsHungry, false);
	
	//lumberjack
	WorldStates.Emplace(WorldState::HaveWood, false);
	WorldStates.Emplace(WorldState::HaveAxe, true);

	//economics
	WorldStates.Emplace(WorldState::HaveMoney, false);
}

void UGOAPBrainComponent::SetActions()
{
	AddAction(CreateDefaultSubobject<UChopTree>("Action_ChopTree"));
	AddAction(CreateDefaultSubobject<USellWood>("Action_SellWood"));
	AddAction(CreateDefaultSubobject<UDrinkWater>("Action_DrinkWater"));
	AddAction(CreateDefaultSubobject<UEatFood>("Action_EatFood"));

	AddAction(CreateDefaultSubobject<UGoToTree>("Action_GoToTree"));
	AddAction(CreateDefaultSubobject<UGoToBuyer>("Action_GoToBuyer"));
	AddAction(CreateDefaultSubobject<UGoToSeller>("Action_GoToSeller"));
}

void UGOAPBrainComponent::SetGoals()
{	
	//Previous element has higher priority
	Goals.Emplace(Precondition{ WorldState::IsInDanger, true }, DesiredState{ WorldState::IsInDanger, false });
	
	Goals.Emplace(Precondition{ WorldState::IsDamaged, true }, DesiredState{ WorldState::IsDamaged, false });
	Goals.Emplace(Precondition{ WorldState::IsThirsty, true }, DesiredState{ WorldState::IsThirsty, false });
	Goals.Emplace(Precondition{ WorldState::IsHungry, true }, DesiredState{ WorldState::IsHungry, false });

	Goals.Emplace(Precondition{ WorldState::HaveMoney, false }, DesiredState{ WorldState::HaveMoney, true });
}

void UGOAPBrainComponent::AddAction(TObjectPtr<UAction> Action)
{
	const TArray<Consequence>& Consequences = Action.Get()->GetConsequences();
	for (auto& Consq : Consequences)
	{
		if (auto ActionsForConseq = Actions.Find(Consq.first))
			ActionsForConseq->Emplace(Action);
		else
			Actions.Emplace(Consq.first).Emplace(Action);
	}
}

void UGOAPBrainComponent::PrintDebug(DebugMessage Message) const
{
#ifdef UE_BUILD_DEBUG

	if (GEngine)
	{
		switch (Message)
		{
		case DebugMessage::WorldStateNotFound:
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, "UGOAPBrainComponent:: Goal has PC WorldState, but Brain does not have this WorldState");
		}
		break;

		case DebugMessage::NoGoalPreconditionMet:
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, "UGOAPBrainComponent:: Not a single Goals PC was met. No Goal could be set");
		}
		break;

		case DebugMessage::NoActionForDesiredState:
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, "UGOAPBrainComponent:: Chaining actions, but no action has the desired consequence");
		}
		break;

		case DebugMessage::CannotSatisfyPrecondition:
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, "UGOAPBrainComponent:: Chaining actions, but precondition could not be satisfied");
		}
		break;

		case DebugMessage::FailedToCreateChainForGoal:
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, "UGOAPBrainComponent:: Failed to create an action chain for the goal");
		}
		break;

		default:
			{
				GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, "UGOAPBrainComponent:: default error report");
			}
			break;
		}
	}

#endif
}
