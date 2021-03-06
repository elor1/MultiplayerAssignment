// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MultiplayerGameGameModeBase.generated.h"

class APlayerCharacter;
/**
 * 
 */
UCLASS()
class MULTIPLAYERGAME_API AMultiplayerGameGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	void PostLogin(APlayerController* NewPlayer) override;
	void PlayerFinished(APlayerCharacter* Player);
};
