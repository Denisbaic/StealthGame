// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "FPSGameMode.h"
#include "FPSHUD.h"
#include "FPSCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"

AFPSGameMode::AFPSGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/BP_Player"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AFPSHUD::StaticClass();
}

void AFPSGameMode::CompleteMission(APawn* InstigatorPawn)
{
	if(InstigatorPawn)
	{
		InstigatorPawn->DisableInput(nullptr);
		TArray<AActor*> ReturnedActors;
		UGameplayStatics::GetAllActorsOfClass(this, SpectatingViewpointCLass, ReturnedActors);
		if(ReturnedActors.Num()==0)
		{
			UE_LOG(LogTemp, Warning, TEXT("SpectatingViewpointClass is nullptr. Please update GameMode class with valid subclass. Cannot change spectating view target."));
			return;
		}

		APlayerController* PC = Cast<APlayerController>(InstigatorPawn->GetController());
		if(PC)
		{
			PC->SetViewTargetWithBlend(ReturnedActors[0], BlendToCamera, EViewTargetBlendFunction::VTBlend_Cubic);
		}
	}

	
	OnMissionCompleted(InstigatorPawn);

	
}
