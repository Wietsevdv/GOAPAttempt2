// Fill out your copyright notice in the Description page of Project Settings.


#include "GOAPCharacter.h"
#include "GOAPController.h"

// Sets default values
AGOAPCharacter::AGOAPCharacter() :
	Super()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AIControllerClass = AGOAPController::StaticClass();
}

// Called when the game starts or when spawned
void AGOAPCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (auto Temp = Cast<AGOAPController>(Controller))
	{
		GOAPController = Temp;
	}
}

// Called every frame
void AGOAPCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
