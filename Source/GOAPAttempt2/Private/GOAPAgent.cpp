// Fill out your copyright notice in the Description page of Project Settings.


#include "GOAPAgent.h"
#include "GOAPController.h"
#include "Axe.h"

// Sets default values
AGOAPAgent::AGOAPAgent() :
	Super(),
	bIsChoppingTree{ false },
	Axe{ nullptr }
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AIControllerClass = AGOAPController::StaticClass();
}

// Called when the game starts or when spawned
void AGOAPAgent::BeginPlay()
{
	Super::BeginPlay();

	if (auto CastedController = Cast<AGOAPController>(Controller))
	{
		GOAPController = CastedController;
	}
}

// Called every frame
void AGOAPAgent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGOAPAgent::SetAxe(TObjectPtr<AAxe> NewAxe)
{
	if (NewAxe.Get())
	{
		Axe = NewAxe;
		Axe->SetOwner(this);

		FAttachmentTransformRules ATRules{ EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepRelative, true };
		FAttachmentTransformRules ATRules2{ EAttachmentRule::SnapToTarget, false };

		Axe->AttachToComponent(GetComponentByClass<USkeletalMeshComponent>(), ATRules, "AxeSocket");
	}
}

void AGOAPAgent::DestroyAxe()
{
	if (Axe.Get())
		Axe->Destroy();
}