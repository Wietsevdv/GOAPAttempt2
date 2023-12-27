// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BrainComponent.h"

#include <utility>
#include <queue>
#include "WorldStates.h"

#include "GOAPBrainComponent.generated.h"

class AGOAPController;
class AGOAPAgent;
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

	//this variable's sole purpose is to prevent the actions from being garbage collected
	//Not sure if I can do this without creating this extra array since using UPropery on the map gives the error that I can't use TArray<UAction*> as a value for the map
	UPROPERTY()
	TArray<UAction*> AllActions;

	TMap<WorldState, TArray<TObjectPtr<UAction>>> Actions;

	TArray<ConditionalGoal> Goals;
	//TArray<TConditionalGoal> TGoals;

	DesiredState CurrentGoal;

	std::queue<TObjectPtr<UAction>> ActionChain;

	TObjectPtr<AGOAPController> OwningController;
	TObjectPtr<AGOAPAgent> GOAPAgent;

private:
	//returns true when a new chain should be created
	void UpdateGoal();
	void DecideGoal(DesiredState& NewGoal) const;
	void CreateChain();
	bool ChainActionFor(const DesiredState& DS, TMap<WorldState, bool>& WorldStatesCopy);
	bool IsAnyPreconditionFalse(const TArray<Precondition>& Preconditions, TArray<Precondition>& UnmetPreconditions, const TMap<WorldState, bool>& WorldStatesCopy);
	void ExecuteChain(float DeltaTime);
	void ApplyWorldStateChanges(TObjectPtr<UAction> Action, TMap<WorldState, bool>& WorldStatesToChange);
	void ApplyWorldStateChanges(const TArray<Consequence>& Consequences, TMap<WorldState, bool>& WorldStatesToChange);
	void ClearChain();

	void SetWorldStates();
	void SetActions();
	void SetGoals();

	void AddAction(TObjectPtr<UAction> Action);

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
