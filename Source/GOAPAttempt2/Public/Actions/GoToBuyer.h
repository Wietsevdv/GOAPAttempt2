// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Action.h"
#include "GoToBuyer.generated.h"

class ABuyer;

UCLASS()
class GOAPATTEMPT2_API UGoToBuyer : public UAction
{
	GENERATED_BODY()
	
private:
	TObjectPtr<ABuyer> Buyer{ nullptr };
	bool bHasReached{ false };

	void SetHasReached() { bHasReached = true; }

	inline static const TArray<Precondition> Preconditions{  };
	inline static const TArray<Consequence> Consequences{ { WorldState::IsNearBuyer, true }, { WorldState::IsNearTree, false }, { WorldState::IsNearSeller, false } };

public:
	virtual const TArray<Precondition>& GetPreconditions() const override { return Preconditions; }
	virtual const TArray<Consequence>& GetConsequences() const override { return Consequences; }

	virtual void Execute(TObjectPtr<AGOAPController> AgentController, bool& bActionFinished, float DeltaTime) override;
};
