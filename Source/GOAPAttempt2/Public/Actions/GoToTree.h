// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Action.h"
#include "GoToTree.generated.h"

class ATree;

UCLASS()
class GOAPATTEMPT2_API UGoToTree : public UAction
{
	GENERATED_BODY()
	
private:
	TObjectPtr<ATree> Tree{ nullptr };
	bool bHasReached{ false };

	void SetHasReached() { bHasReached = true; }

	inline static const TArray<Precondition> Preconditions{  };
	inline static const TArray<Consequence> Consequences{ { WorldState::IsNearTree, true }, { WorldState::IsNearBuyer, false }, { WorldState::IsNearSeller, false } };

public:
	virtual const TArray<Precondition>& GetPreconditions() const override { return Preconditions; }
	virtual const TArray<Consequence>& GetConsequences() const override { return Consequences; }

	virtual void Execute(TObjectPtr<AGOAPAgent> Agent, TObjectPtr<AGOAPController> AgentController, bool& bActionFinished, float DeltaTime) override;
};
