// Fill out your copyright notice in the Description page of Project Settings.


#include "LaunchPad.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/DecalComponent.h"
#include "FPSCharacter.h"
#include "Kismet/GameplayStatics.h"
// Sets default values
ALaunchPad::ALaunchPad()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;

	Plane = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Plane"));
	Plane->SetupAttachment(Mesh);

	OverlapComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapComponent"));
	OverlapComponent->SetupAttachment(Mesh);
	OverlapComponent->OnComponentBeginOverlap.AddDynamic(this, &ALaunchPad::OnHandleOverlap);

}

// Called when the game starts or when spawned
void ALaunchPad::BeginPlay()
{
	Super::BeginPlay();
	
}

void ALaunchPad::OnHandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	FRotator LaunchDirection = GetActorRotation();
	LaunchDirection.Pitch += LaunchPitchAngle;

	AFPSCharacter* Character = Cast<AFPSCharacter>(OtherActor);
	if(Character)
	{
		
		Character->LaunchCharacter(LaunchDirection.Vector()*LaunchStrength, true, true);
		UGameplayStatics::SpawnEmitterAtLocation(this, LaunchFX, GetActorLocation()+FVector(0.f,0.f,100.f));
	}
	else
	{
		if(OtherComp->IsSimulatingPhysics())
		{
			OtherComp->AddImpulse(LaunchDirection.Vector()* LaunchStrength,NAME_None,true);
			UGameplayStatics::SpawnEmitterAtLocation(this, LaunchFX, GetActorLocation() + FVector(0.f, 0.f, 100.f));
		}
	}
}

// Called every frame
void ALaunchPad::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

