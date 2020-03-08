// Fill out your copyright notice in the Description page of Project Settings.


#include "GuardController.h"
#include "FPSAIGuard.h"

void AGuardController::BeginPlay()
{
	Super::BeginPlay();
	AFPSAIGuard* Guard = Cast<AFPSAIGuard>(GetPawn());
	PointActor = Guard->TargetActor1;
}

void AGuardController::Tick(float DeltaSeconds)
{
	AFPSAIGuard* Guard = Cast<AFPSAIGuard>(GetPawn());

	if(Guard->GetGuardState() == EAIState::Idle)
	{
		if (MoveToActor(PointActor, 300.f) == EPathFollowingRequestResult::Type::AlreadyAtGoal)
		{
			ChooseNextPoint();
		}
	}
	else if(Guard->GetGuardState()== EAIState::Suspicious)
	{
		StopMovement();
	}
}

void AGuardController::ChooseNextPoint()
{
	AFPSAIGuard* Guard = Cast<AFPSAIGuard>(GetPawn());
	if(PointActor== Guard->TargetActor1)
	{
		PointActor = Guard->TargetActor2;
	}
	else
	{
		PointActor = Guard->TargetActor1;
	}
}
