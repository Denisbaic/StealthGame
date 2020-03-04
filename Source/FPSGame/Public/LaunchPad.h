// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LaunchPad.generated.h"

UCLASS()
class FPSGAME_API ALaunchPad : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALaunchPad();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Components")
		UStaticMeshComponent* Mesh;
	UPROPERTY(EditAnywhere, Category = "Components")
		UStaticMeshComponent* Plane;
	UPROPERTY(EditAnywhere, Category = "Components")
		class UBoxComponent* OverlapComponent;
	UPROPERTY(EditAnywhere,  Category = "Components")
		UParticleSystem* LaunchFX;

	UPROPERTY(EditAnywhere, Category = "Launch config")
		float LaunchPitchAngle=35.f;
	UPROPERTY(EditAnywhere, Category = "Launch config")
		float LaunchStrength=1500.f;
public:
	UFUNCTION(BlueprintCallable)
		void OnHandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
			UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
