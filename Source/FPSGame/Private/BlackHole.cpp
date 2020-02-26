// Fill out your copyright notice in the Description page of Project Settings.


#include "BlackHole.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
// Sets default values
ABlackHole::ABlackHole()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	DestroySphere = CreateDefaultSubobject<USphereComponent>(TEXT("DestroySphere"));
	GravitySphere = CreateDefaultSubobject<USphereComponent>(TEXT("GravitySphere"));

	RootComponent = MeshComponent;

	MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MeshComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	MeshComponent->SetGenerateOverlapEvents(false);

	GravitySphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	GravitySphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	GravitySphere->SetCollisionResponseToAllChannels(ECR_Overlap);
	GravitySphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);

	DestroySphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	DestroySphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	DestroySphere->SetCollisionResponseToAllChannels(ECR_Overlap);
	DestroySphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);

	
}

// Called when the game starts or when spawned
void ABlackHole::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABlackHole::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TArray<AActor*> OverlappedActors;
	GetOverlappingActors(OverlappedActors);
	for (auto elem : OverlappedActors)
	{
		UStaticMeshComponent* MeshComponent=Cast<UStaticMeshComponent>(elem->GetComponentByClass(UMeshComponent::StaticClass()));
		if(MeshComponent)
		{
			MeshComponent->AddRadialForce(GetActorLocation(), GravitySphere->GetScaledSphereRadius(), BlackHoleStrength, ERadialImpulseFalloff::RIF_Constant, false);
		}
	}
	OverlappedActors.Empty();
	DestroySphere->GetOverlappingActors(OverlappedActors);
	OverlappedActors.RemoveAt(OverlappedActors.Find(this));
	for (auto elem : OverlappedActors)
	{
		elem->Destroy();
	}
}

