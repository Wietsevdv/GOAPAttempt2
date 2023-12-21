// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Action.h"
#include "BuyAxe.generated.h"

class ASeller;

UCLASS()
class GOAPATTEMPT2_API UBuyAxe : public UAction
{
	GENERATED_BODY()
	
private:
	float Timer{ 0.f };
	TObjectPtr<ASeller> Seller{ nullptr };

	inline static const TArray<Precondition> Preconditions{ { WorldState::IsNearSeller, true }, { WorldState::HaveMoney, true } };
	inline static const TArray<Consequence> Consequences{ { WorldState::HaveMoney, false }, { WorldState::HaveAxe, true } };

public:
	virtual const TArray<Precondition>& GetPreconditions() const override { return Preconditions; }
	virtual const TArray<Consequence>& GetConsequences() const override { return Consequences; }

	virtual void Execute(TObjectPtr<AGOAPAgent> Agent, TObjectPtr<AGOAPController> AgentController, bool& bActionFinished, float DeltaTime) override;
};
