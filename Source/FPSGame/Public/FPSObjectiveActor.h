// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSObjectiveActor.generated.h"

class USphereComponent;

UCLASS()
class FPSGAME_API AFPSObjectiveActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFPSObjectiveActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnywhere,Category="Components")
		UStaticMeshComponent* MeshComponent;
	UPROPERTY(VisibleAnywhere, Category = "Components")
		USphereComponent*  Sphere;
	UPROPERTY(EditAnywhere, Category = "Components")
	UParticleSystem* PickupFX;

	void PlayEffects();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void NotifyActorBeginOverlap(AActor* OtherActor) override;
};