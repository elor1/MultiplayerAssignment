// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "SlidingDoor.generated.h"

UENUM()
enum class ESlideState : uint8
{
	Up,
	Down,
	Pause
};

/**
 * 
 */
UCLASS()
class MULTIPLAYERGAME_API ASlidingDoor : public AStaticMeshActor
{
	GENERATED_BODY()

public:
	ASlidingDoor();

	void Tick(float DeltaSeconds) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	void BeginPlay() override;

private:
	UPROPERTY(Replicated)
	ESlideState SlideState = ESlideState::Pause;

	UPROPERTY(Replicated)
	float MaxHeight;

	UPROPERTY(Replicated)
	float CurrentHeight;

	FTimerHandle PauseTimer;
	
	UPROPERTY(EditAnywhere)
	float MinHeight = -90.0f;

	UPROPERTY(EditAnywhere)
	float MinSpeed = 150.0f;

	UPROPERTY(EditAnywhere)
	float MaxSpeed = 350.0f;
	
	UPROPERTY(Replicated)
	float Speed = 200.0f;

	UPROPERTY(EditAnywhere)
	float MinPauseTime = 1.0f;

	UPROPERTY(EditAnywhere)
	float MaxPauseTime = 2.5f;

	UFUNCTION(NetMulticast, Reliable)
	void SetStatePaused();

	UFUNCTION(NetMulticast, Reliable)
	void SetStateUp();

	UFUNCTION(NetMulticast, Reliable)
	void SetStateDown();
};
