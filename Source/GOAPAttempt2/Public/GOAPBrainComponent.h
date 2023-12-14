// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BrainComponent.h"

#include <utility>
#include <stack>
#include "WorldStates.h"

#include "GOAPBrainComponent.generated.h"

class UAction;

UCLASS()
class GOAPATTEMPT2_API UGOAPBrainComponent : public UBrainComponent
{
	GENERATED_BODY()
	
public:
	UGOAPBrainComponent();

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	TMap<WorldState, bool> WorldStates;
	TMap<WorldState, TArray<TObjectPtr<UAction>>> Actions;
	TArray<Goal> Goals;

	Goal CurrentGoal;
	std::stack<TObjectPtr<UAction>> ActionChain;

	bool DoOnce;

private:
	//returns true when a new chain should be created
	void DecideGoal(Goal& NewGoal) const;
	void CreateChain();
	bool ChainActionFor(const DesiredState& DS);
	void ExecuteChain(float DeltaTime);
	void ClearChain();

	void SetWorldStates();
	void SetActions();
	void SetGoals();

	void AddAction(TObjectPtr<UAction>);

	enum class DebugMessage
	{
		WorldStateNotFound,
		NoGoalPreconditionMet,
		NoActionForDesiredState,
		CannotSatisfyPrecondition,
		FailedToCreateChainForGoal
	};
	void PrintDebug(DebugMessage Message, UAction* Action = nullptr) const;
};
