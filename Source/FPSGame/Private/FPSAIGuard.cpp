// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSAIGuard.h"
#include "Perception/PawnSensingComponent.h"
#include "DrawDebugHelpers.h"
#include "TimerManager.h"
#include "FPSGameMode.h"
#include "Engine/World.h"

// Sets default values
AFPSAIGuard::AFPSAIGuard()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PawnSensingComponent = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));
	PawnSensingComponent->OnSeePawn.AddDynamic(this, &AFPSAIGuard::OnPawnSeen);
	PawnSensingComponent->OnHearNoise.AddDynamic(this, &AFPSAIGuard::OnPawnHeard);
	GuardState = EAIState::Idle;
}

// Called when the game starts or when spawned
void AFPSAIGuard::BeginPlay()
{
	Super::BeginPlay();
	OriginalRotation=GetActorRotation();
}

void AFPSAIGuard::ResetOrientation()
{
	if (GuardState == EAIState::Alerted)
		return;
	SetActorRotation(OriginalRotation);
	SetGuardState(EAIState::Idle);
}

void AFPSAIGuard::SetGuardState(EAIState NewState)
{
	if(GuardState==NewState)
	{
		return;
	}
	GuardState = NewState;

	OnStateChanged(NewState);
}

// Called every frame
void AFPSAIGuard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFPSAIGuard::OnPawnSeen(APawn* SeenPawn)
{
	if(!SeenPawn)
	{
		return;
	}
	DrawDebugSphere(GetWorld(), SeenPawn->GetActorLocation(), 32.0f, 12, FColor::Black, false, 10.f);
	AFPSGameMode* GM = Cast<AFPSGameMode>(GetWorld()->GetAuthGameMode());
	if (GM)
	{
		GM->CompleteMission(SeenPawn, false);
	}
	SetGuardState(EAIState::Alerted);
}

void AFPSAIGuard::OnPawnHeard(APawn* Instigator, const FVector& Location, float Volume)
{
	if (GuardState == EAIState::Alerted)
		return;
	DrawDebugSphere(GetWorld(), Location, 32.0f, 12, FColor::Red, false, 10.f);
	FVector Direction = Location - GetActorLocation();
	Direction.Normalize();
	FRotator NewLookActor=FRotationMatrix::MakeFromX(Direction).Rotator();
	NewLookActor.Pitch = 0.0f;
	NewLookActor.Roll = 0.0f;
	
	SetActorRotation(NewLookActor);
	GetWorldTimerManager().ClearTimer(TimerHandle_ResetOrientation);
	GetWorldTimerManager().SetTimer(TimerHandle_ResetOrientation, this, &AFPSAIGuard::ResetOrientation,3.0f);
	SetGuardState(EAIState::Suspicious);
}
