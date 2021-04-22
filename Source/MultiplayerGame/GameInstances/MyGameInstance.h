// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

class UWidget;
/**
 * 
 */
UCLASS()
class MULTIPLAYERGAME_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	bool bGameStarted = false;
	
	UFUNCTION(Exec)
	void Host();

	UFUNCTION(Exec)
	void Join(const FString IPAddress);

	UFUNCTION(Exec)
	void Warp(const FString LevelName);
};
