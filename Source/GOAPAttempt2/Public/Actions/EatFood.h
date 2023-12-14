// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Action.h"
#include "EatFood.generated.h"

/**
 * 
 */
UCLASS()
class GOAPATTEMPT2_API UEatFood : public UAction
{
	GENERATED_BODY()
	
private:
	inline static const TArray<Precondition> Preconditions{ { WorldState::HaveFood, true } };
	inline static const TArray<Consequence> Consequences{ { WorldState::IsHungry, false } };

public:
	virtual const TArray<Precondition>& GetPreconditions() const { return Preconditions; }
	virtual const TArray<Consequence>& GetConsequences() const { return Consequences; }

	virtual void Execute(TObjectPtr<AGOAPController> AgentController, bool& bActionFinished, float DeltaTime) const override;
};
