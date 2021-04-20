// Copyright Epic Games, Inc. All Rights Reserved.


#include "MultiplayerGameGameModeBase.h"

#include "GameStates/MyGameStateBase.h"

void AMultiplayerGameGameModeBase::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	if (AMyGameStateBase* State = GetGameState<AMyGameStateBase>())
	{
		State->LogPlayerJoin();
	}
}
