// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameStateBase.h"

#include "MultiplayerGame/GameInstances/MyGameInstance.h"
#include "Net/UnrealNetwork.h"

void AMyGameStateBase::LogPlayerJoin()
{
	if (HasAuthority())
	{
		NumPlayers++;

		if (NumPlayers == PlayersToStart)
		{
			if (UMyGameInstance* Instance = Cast<UMyGameInstance>(GetGameInstance()))
			{
				Instance->Warp("Main");
			}
		}
	}
}

void AMyGameStateBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMyGameStateBase, NumPlayers);
}