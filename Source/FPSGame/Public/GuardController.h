// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "GuardController.generated.h"

/**
 * 
 */
UCLASS()
class FPSGAME_API AGuardController : public AAIController
{
	GENERATED_BODY()

	void BeginPlay() override;
	void Tick(float DeltaSeconds) override;
protected:
	AActor* PointActor;

	void ChooseNextPoint();
};
