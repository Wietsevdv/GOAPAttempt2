// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "GOAPController.generated.h"

class UGOAPBrainComponent;
class AGOAPCharacter;

UCLASS()
class GOAPATTEMPT2_API AGOAPController : public AAIController
{
	GENERATED_BODY()
	
	DECLARE_DELEGATE(ReachedGoTo);

private:
	UGOAPBrainComponent* GOAPBrain;
	AGOAPCharacter* GOAPAgent;

	ReachedGoTo DReachedGoTo;

public:
	AGOAPController();

	ReachedGoTo& GetReachedGoToDelegate() { return DReachedGoTo; }
	virtual void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
