	// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "WorldStates.h"

#include "Action.generated.h"

class AGOAPController;
class AGOAPAgent;

UCLASS(Abstract)
class GOAPATTEMPT2_API UAction : public UObject
{
	GENERATED_BODY()

public:
	virtual const TArray<Precondition>& GetPreconditions() const PURE_VIRTUAL(UAction::GetPreconditions, return Empty;);
	virtual const TArray<Consequence>& GetConsequences() const PURE_VIRTUAL(UAction::GetConsequences, return Empty;);
	
	virtual void Execute(TObjectPtr<AGOAPAgent> Agent, TObjectPtr<AGOAPController> AgentController, bool& bActionFinished, float DeltaTime) PURE_VIRTUAL(UAction::UpdateAction, );

protected:
	bool Started{ false };

private:
	const TArray<Precondition> Empty{};
};
