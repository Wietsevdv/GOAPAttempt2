// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Action.h"
#include "GoToSeller.generated.h"

class ASeller;

UCLASS()
class GOAPATTEMPT2_API UGoToSeller : private UAction
{
	GENERATED_BODY()

private:
	TObjectPtr<ASeller> Seller{ nullptr };

	inline static const TArray<Precondition> Preconditions{  };
	inline static const TArray<Consequence> Consequences{ { WorldState::IsNearSeller, true } };

public:
	virtual const TArray<Precondition>& GetPreconditions() const { return Preconditions; }
	virtual const TArray<Consequence>& GetConsequences() const { return Consequences; }

	virtual void Execute(TObjectPtr<AGOAPController> AgentController, bool& bActionFinished, float DeltaTime) override;
};
