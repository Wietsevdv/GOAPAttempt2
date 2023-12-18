// Fill out your copyright notice in the Description page of Project Settings.


#include "GOAPBrainComponent.h"
#include "GOAPController.h"

#include "Actions/ChopTree.h"
#include "Actions/SellWood.h"
#include "Actions/BuyAxe.h"
#include "Actions/EatFood.h"
#include "Actions/DrinkWater.h"

#include "Actions/GoToTree.h"
#include "Actions/GoToSeller.h"
#include "Actions/GoToBuyer.h"

UGOAPBrainComponent::UGOAPBrainComponent() :
	Super(),
	CurrentGoal{ WorldState::Chilling, true },		//guaranteed to be overwritten (for now)+=
	OwningController{ nullptr }
{
	SetWorldStates();
	SetActions();
	SetGoals();
}

void UGOAPBrainComponent::BeginPlay()
{
	Super::BeginPlay();
	
	OwningController = Cast<AGOAPController>(GetOwner());
}

void UGOAPBrainComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	UpdateGoal();
	ExecuteChain(DeltaTime);
}

void UGOAPBrainComponent::UpdateGoal()
{	
	DesiredState NewGoal{ WorldState::Chilling, true };		//guaranteed to be overwritten (for now)
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
	}
}

void UGOAPBrainComponent::DecideGoal(DesiredState& NewGoal) const
{
	for (const ConditionalGoal& Goal : Goals)
	{
		const bool* State = WorldStates.Find(Goal.first.first);
		if (State && *State == Goal.first.second)
		{
			NewGoal = Goal.second;
			return;
		}

		if (State == nullptr)
			PrintDebug(DebugMessage::WorldStateNotFound);
	}
}

void UGOAPBrainComponent::CreateChain()
{
	TMap<WorldState, bool> WorldStatesCopy{ WorldStates };
	if (!ChainActionFor(CurrentGoal, WorldStatesCopy))
	{
		PrintDebug(DebugMessage::FailedToCreateChainForGoal);
	}
}

bool UGOAPBrainComponent::ChainActionFor(const DesiredState& DS, TMap<WorldState, bool>& WorldStatesCopy)
{
	auto ActionsThatEffectDSWorldStateP = Actions.Find(DS.first);
	if (ActionsThatEffectDSWorldStateP == nullptr || ActionsThatEffectDSWorldStateP->Num() == 0)
	{
		PrintDebug(DebugMessage::NoActionForDesiredState);
		return false;
	}

	for (TObjectPtr<UAction> Action : *ActionsThatEffectDSWorldStateP)
	{
		const auto& Consequences = Action->GetConsequences();
		if (Consequences.Find(DS) != INDEX_NONE)
		{
			//a chained action can change the WorldStateCopy needing other actions to satisfy PC that were previously satisfied but not anymore, so -> while-loop
			TArray<Precondition> PreconditionsToSatisfy{};
			const TArray<Precondition>& Preconditions = Action->GetPreconditions();
			while (IsAnyPreconditionFalse(Preconditions, PreconditionsToSatisfy, WorldStatesCopy))
			{
				for (const auto& Precondition : PreconditionsToSatisfy)
				{
					if (!ChainActionFor(Precondition, WorldStatesCopy))
					{
						//this is wrong, when an action cannot chain try other possibilities instead of immediately returning false
						//comparing different options is for later (KISS), need a more complex example anyway
						PrintDebug(DebugMessage::CannotSatisfyPrecondition, Action);
						return false;
					}
				}
			}
			
			ApplyWorldStateChanges(Consequences, WorldStatesCopy);
			ActionChain.push(Action);

			return true;
		}
	}

	return false;
}

bool UGOAPBrainComponent::IsAnyPreconditionFalse(const TArray<Precondition>& Preconditions, TArray<Precondition>& UnmetPreconditions, const TMap<WorldState, bool>& WorldStatesCopy)
{
	bool bHasFalsePrecondition{ false };
	UnmetPreconditions.Empty();

	for (const auto& Precondition : Preconditions)
	{
		if (*WorldStatesCopy.Find(Precondition.first) == Precondition.second)
			continue;
		else
		{
			UnmetPreconditions.Add(Precondition);
			bHasFalsePrecondition = true;
		}
	}

	return bHasFalsePrecondition;
}

void UGOAPBrainComponent::ExecuteChain(float DeltaTime)
{
	if (ActionChain.empty())
		return;

	bool bIsActionFinished{ false };
	TObjectPtr<UAction> TopAction = ActionChain.front();

	TopAction->Execute(OwningController, bIsActionFinished, DeltaTime);
	if (bIsActionFinished)
	{
		ApplyWorldStateChanges(TopAction, WorldStates);
		ActionChain.pop();
	}
}

void UGOAPBrainComponent::ApplyWorldStateChanges(TObjectPtr<UAction> Action, TMap<WorldState, bool>& WorldStatesToChange)
{
	ApplyWorldStateChanges(Action->GetConsequences(), WorldStatesToChange);
}

void UGOAPBrainComponent::ApplyWorldStateChanges(const TArray<Consequence>& Consequences, TMap<WorldState, bool>& WorldStatesToChange)
{
	for (const auto& Consequence : Consequences)
	{
		if (bool* State = WorldStatesToChange.Find(Consequence.first))
		{
			*State = Consequence.second;
		}
	}
}

void UGOAPBrainComponent::ClearChain()
{
	if (!ActionChain.empty())
		ActionChain = std::queue<TObjectPtr<UAction>>();
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
	WorldStates.Emplace(WorldState::HaveWater, true);	//true for now
	WorldStates.Emplace(WorldState::HaveFood, true);	//true for now

	//locations
	WorldStates.Emplace(WorldState::IsNearTree, false);
	WorldStates.Emplace(WorldState::IsNearBuyer, false);
	WorldStates.Emplace(WorldState::IsNearSeller, false);
}

void UGOAPBrainComponent::SetActions()
{
	AddAction(CreateDefaultSubobject<UChopTree>("Action_ChopTree"));
	AddAction(CreateDefaultSubobject<USellWood>("Action_SellWood"));
	AddAction(CreateDefaultSubobject<UBuyAxe>("Action_BuyAxe"));
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
	Goals.Emplace(Precondition{ WorldState::HaveAxe, false }, DesiredState{ WorldState::HaveAxe, true });
}

void UGOAPBrainComponent::AddAction(TObjectPtr<UAction> Action)
{
	AllActions.Add(Action.Get());

	const TArray<Consequence>& Consequences = Action->GetConsequences();
	for (auto& Consq : Consequences)
	{
		if (auto ActionsForConseq = Actions.Find(Consq.first))
			ActionsForConseq->Emplace(Action);
		else
			Actions.Emplace(Consq.first).Emplace(Action);
	}
}

void UGOAPBrainComponent::PrintDebug(DebugMessage Message, UAction* Action) const
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
			if (Action)
			{
				GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Magenta, Action->GetName());
				GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Magenta, Action->GetFName().ToString());
			}
		}
		break;

		case DebugMessage::CannotSatisfyPrecondition:
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, "UGOAPBrainComponent:: Chaining actions, but precondition could not be satisfied");
			if (Action)
			{
				GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Magenta, Action->GetName());
				GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Magenta, Action->GetFName().ToString());
			}
		}
		break;

		case DebugMessage::FailedToCreateChainForGoal:
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, "UGOAPBrainComponent:: Failed to create an action chain for the goal");
		}
		break;
		}
	}

#endif
}
