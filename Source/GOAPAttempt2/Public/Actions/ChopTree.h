// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Action.h"
#include "ChopTree.generated.h"

class ATree;

UCLASS()
class GOAPATTEMPT2_API UChopTree : private UAction
{
	GENERATED_BODY()
	
private:
	TObjectPtr<ATree> Tree{ nullptr };
	float Timer{ 0.f };

	inline static const TArray<Precondition> Preconditions{ { WorldState::HaveAxe, true }, { WorldState::IsNearTree, true } };
	inline static const TArray<Consequence> Consequences{ { WorldState::HaveWood, true } };

public:
	virtual const TArray<Precondition>& GetPreconditions() const { return Preconditions; }
	virtual const TArray<Consequence>& GetConsequences() const { return Consequences; }

	virtual void Execute(TObjectPtr<AGOAPController> AgentController, bool& bActionFinished, float DeltaTime) override;
};
