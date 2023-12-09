// Fill out your copyright notice in the Description page of Project Settings.


#include "GOAPBrainComponent.h"

UGOAPBrainComponent::UGOAPBrainComponent()
{
	SetWorldStates();
	SetGoals();
}

void UGOAPBrainComponent::BeginPlay()
{
}

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

void UGOAPBrainComponent::SetGoals()
{	
	//Previous element has higher priority
	Goals.Emplace(Precondition{ WorldState::IsInDanger, true }, DesiredState{ WorldState::IsInDanger, false });
	
	Goals.Emplace(Precondition{ WorldState::IsDamaged, true }, DesiredState{ WorldState::IsDamaged, false });
	Goals.Emplace(Precondition{ WorldState::IsThirsty, true }, DesiredState{ WorldState::IsThirsty, false });
	Goals.Emplace(Precondition{ WorldState::IsHungry, true }, DesiredState{ WorldState::IsHungry, false });

	Goals.Emplace(Precondition{ WorldState::HaveMoney, false }, DesiredState{ WorldState::HaveMoney, true });
}
