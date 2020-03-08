// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Navigation/PathFollowingComponent.h"
#include "FPSAIGuard.generated.h"
struct FAIRequestID;
UENUM(BlueprintType)
enum  class EAIState:uint8
{
	Idle, Suspicious, Alerted
};
UCLASS()
class FPSGAME_API AFPSAIGuard : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPSAIGuard();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnywhere,Category="Components")
		class UPawnSensingComponent* PawnSensingComponent;

	UFUNCTION()
		void OnPawnSeen(APawn* SeenPawn);
	UFUNCTION()
		void OnPawnHeard(APawn* _Instigator, const FVector& _Location, float _Volume);
	UPROPERTY()
		FRotator OriginalRotation;
	UFUNCTION()
	void ResetOrientation();
	FTimerHandle TimerHandle_ResetOrientation;

	EAIState GuardState;


	UPROPERTY(EditAnywhere, Category = "Components")
		bool bCanPatrol;

	UFUNCTION(BlueprintImplementableEvent, Category="AI")
		void OnStateChanged(EAIState NewState);
public:

	void SetGuardState(EAIState NewState);
	EAIState GetGuardState();
	UPROPERTY(EditInstanceOnly, Category = "Components", meta=(EditCondition="bCanPatrol"))
		AActor* TargetActor1;
	UPROPERTY(EditInstanceOnly, Category = "Components", meta = (EditCondition = "bCanPatrol"))
		AActor* TargetActor2;

	AActor* PointActor;
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION()
	void ChooseNextPoint(FAIRequestID RequestID, EPathFollowingResult::Type Result);

};
