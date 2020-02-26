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

	GravitySphere->SetCollisionObjectType(ECC_WorldStatic);
	GravitySphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	GravitySphere->SetCollisionResponseToAllChannels(ECR_Overlap);
	GravitySphere->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Ignore);
	GravitySphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);

	DestroySphere->SetCollisionObjectType(ECC_WorldStatic);
	DestroySphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	DestroySphere->SetCollisionResponseToAllChannels(ECR_Overlap);
	DestroySphere->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Ignore);
	DestroySphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);	

	DestroySphere->OnComponentBeginOverlap.AddDynamic(this, &ABlackHole::OnDestroySphereHit);
	
}

// Called when the game starts or when spawned
void ABlackHole::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABlackHole::OnDestroySphereHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
		OtherActor->Destroy();
}

// Called every frame
void ABlackHole::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TArray<UPrimitiveComponent*> OverlappedComponents;
	GravitySphere->GetOverlappingComponents(OverlappedComponents);
	for (auto elem : OverlappedComponents)
	{
		if(elem && elem->IsSimulatingPhysics())
		{
			elem->AddRadialForce(GetActorLocation(), GravitySphere->GetScaledSphereRadius(), BlackHoleStrength, ERadialImpulseFalloff::RIF_Constant, false);
		}
	}
}

