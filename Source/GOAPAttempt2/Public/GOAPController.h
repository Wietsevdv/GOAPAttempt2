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
	
public:
	AGOAPController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UGOAPBrainComponent* GOAPBrain;
	AGOAPCharacter* GOAPAgent;
};
