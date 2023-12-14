	// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "WorldStates.h"

#include "Action.generated.h"

class AGOAPController;

UCLASS(Abstract)
class GOAPATTEMPT2_API UAction : public UObject
{
	GENERATED_BODY()

public:
	virtual const TArray<Precondition>& GetPreconditions() const PURE_VIRTUAL(UAction::GetPreconditions, return Preconditions;);
	virtual const TArray<Consequence>& GetConsequences() const PURE_VIRTUAL(UAction::GetConsequences, return Consequences;);

	virtual void Execute(TObjectPtr<AGOAPController> AgentController, bool& bActionFinished, float DeltaTime) const PURE_VIRTUAL(UAction::UpdateAction, );

private:
	const TArray<Precondition> Preconditions{};
	const TArray<Consequence> Consequences{};
};
