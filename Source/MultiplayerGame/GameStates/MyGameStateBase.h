// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "MyGameStateBase.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYERGAME_API AMyGameStateBase : public AGameStateBase
{
	GENERATED_BODY()

public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	void LogPlayerJoin();

	UPROPERTY(BlueprintReadOnly, Replicated)
	int NumPlayers = 0;

private:
	UPROPERTY(EditAnywhere)
	int PlayersToStart = 4;
};
