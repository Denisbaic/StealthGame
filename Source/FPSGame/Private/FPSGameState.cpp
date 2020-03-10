// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSGameState.h"
#include "Engine/World.h"
#include "FPSPlayerController.h"

void AFPSGameState::MulticastOnMissionComplete_Implementation(APawn* InstigatorPawn, bool bIsMissionComplete)
{
	//for (FConstPawnIterator It = GetWorld()->GetPawnIterator(); It; ++It)
	//{
	//	APawn* Pawn = It->Get();
	//	if(Pawn && Pawn->IsLocallyControlled())
	//	{
	//		Pawn->DisableInput(nullptr);
	//	}
	//}
	for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
	{
		AFPSPlayerController* PC = Cast<AFPSPlayerController>(It->Get());
		if(PC && PC->IsLocalController())
		{
			PC->OnMissionComplete(InstigatorPawn, bIsMissionComplete);
			APawn* Pawn = PC->GetPawn();
			if (Pawn && Pawn->IsLocallyControlled())
			{
				Pawn->DisableInput(nullptr);
			}
		}
	}
}