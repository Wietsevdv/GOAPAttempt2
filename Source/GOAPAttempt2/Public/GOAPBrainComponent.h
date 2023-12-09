// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BrainComponent.h"

#include <utility>
#include "WorldStates.h"

#include "GOAPBrainComponent.generated.h"



UCLASS()
class GOAPATTEMPT2_API UGOAPBrainComponent : public UBrainComponent
{
	GENERATED_BODY()
	
public:
	UGOAPBrainComponent();

protected:
	virtual void BeginPlay() override;

private:
	TArray<std::pair<WorldState, bool>> WorldStates;

	TArray<Goal> Goals;

private:
	void SetWorldStates();
	void SetGoals();
};
