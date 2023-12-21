// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Action.h"
#include "SellWood.generated.h"

class ASeller;

UCLASS()
class GOAPATTEMPT2_API USellWood : public UAction
{
	GENERATED_BODY()
	
private:
	float Timer{ 0.f };
	TObjectPtr<ASeller> Seller{ nullptr };

	inline static const TArray<Precondition> Preconditions{ { WorldState::HaveWood, true }, { WorldState::IsNearBuyer, true } };
	inline static const TArray<Consequence> Consequences{ { WorldState::HaveWood, false }, { WorldState::HaveMoney, true } };

public:
	virtual const TArray<Precondition>& GetPreconditions() const override { return Preconditions; }
	virtual const TArray<Consequence>& GetConsequences() const override { return Consequences; }

	virtual void Execute(TObjectPtr<AGOAPAgent> Agent, TObjectPtr<AGOAPController> AgentController, bool& bActionFinished, float DeltaTime) override;
};
