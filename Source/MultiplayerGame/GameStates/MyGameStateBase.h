// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "MyGameStateBase.generated.h"

class APlayerCharacter;
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

	void LogPlayerFinished(APlayerCharacter* Player);

	UPROPERTY(BlueprintReadOnly, Replicated)
	int NumPlayers = 0;

	UPROPERTY(BlueprintReadOnly, Replicated)
	int PlayersFinished = 0;

private:
	UPROPERTY(EditAnywhere)
	int PlayersToStart = 4;
};
