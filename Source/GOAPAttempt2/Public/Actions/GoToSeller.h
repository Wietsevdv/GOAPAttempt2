// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Action.h"
#include "GoToSeller.generated.h"

class ASeller;

UCLASS()
class GOAPATTEMPT2_API UGoToSeller : public UAction
{
	GENERATED_BODY()

private:
	TObjectPtr<ASeller> Seller{ nullptr };
	bool bHasReached{ false };

	void SetHasReached() { bHasReached = true; }

	inline static const TArray<Precondition> Preconditions{  };
	inline static const TArray<Consequence> Consequences{ { WorldState::IsNearSeller, true }, { WorldState::IsNearTree, false }, { WorldState::IsNearBuyer, false } };

public:
	virtual const TArray<Precondition>& GetPreconditions() const override { return Preconditions; }
	virtual const TArray<Consequence>& GetConsequences() const override { return Consequences; }

	virtual void Execute(TObjectPtr<AGOAPAgent> Agent, TObjectPtr<AGOAPController> AgentController, bool& bActionFinished, float DeltaTime) override;
};
