// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GOAPAgent.generated.h"

class AGOAPController;
class AAxe;

UCLASS()
class GOAPATTEMPT2_API AGOAPAgent : public ACharacter
{
	GENERATED_BODY()

private:
	TObjectPtr<AGOAPController> GOAPController;

	bool bIsChoppingTree;
	TObjectPtr<AAxe> Axe;

public:
	// Sets default values for this character's properties
	AGOAPAgent();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	const bool IsChoppingTree() const { return bIsChoppingTree; }
	void SetIsChoppingTree(bool IsChoppingTree) { bIsChoppingTree = IsChoppingTree; }

	void SetAxe(TObjectPtr<AAxe> NewAxe);
	void DestroyAxe();

};
