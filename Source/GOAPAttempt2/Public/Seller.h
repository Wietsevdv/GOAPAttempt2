// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Seller.generated.h"

class AAxe;

UCLASS()
class GOAPATTEMPT2_API ASeller : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AAxe> BPAxe;

public:	
	// Sets default values for this actor's properties
	ASeller();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	AAxe* SellAxe();
};
