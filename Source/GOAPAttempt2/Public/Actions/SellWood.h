// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Action.h"
#include "SellWood.generated.h"

/**
 * 
 */
UCLASS()
class GOAPATTEMPT2_API USellWood : public UAction
{
	GENERATED_BODY()
	
public:
	const TArray<Precondition> Preconditions{ { WorldState::HaveWood, true }, { WorldState::IsNearBuyer, true } };
	const TArray<Consequence> Consequences{ { WorldState::HaveMoney, true } };

public:
	virtual const TArray<Precondition>& GetPreconditions() const { return Preconditions; }
	virtual const TArray<Consequence>& GetConsequences() const { return Consequences; }

	virtual void StartAction(AGOAPController* AgentController) const;
	virtual void UpdateAction(AGOAPController* AgentController, bool& bActionFinished, float DeltaTime) const;
};
