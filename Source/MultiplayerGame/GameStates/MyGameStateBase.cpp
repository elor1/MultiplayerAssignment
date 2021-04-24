// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameStateBase.h"

#include "MultiplayerGame/GameInstances/MyGameInstance.h"
#include "Net/UnrealNetwork.h"
#include "MultiplayerGame/Pawns/PlayerCharacter.h"

void AMyGameStateBase::LogPlayerJoin()
{
	if (UMyGameInstance* Instance = Cast<UMyGameInstance>(GetGameInstance()))
	{
		if (HasAuthority() && !Instance->bGameStarted)
		{
			NumPlayers++;

			if (NumPlayers == PlayersToStart)
			{
				Instance->bGameStarted = true;
				Instance->Warp("Main");
			}
		}
	}
}

void AMyGameStateBase::LogPlayerFinished(APlayerCharacter* Player)
{
	if (UMyGameInstance* Instance = Cast<UMyGameInstance>(GetGameInstance()))
	{
		if (HasAuthority())
		{
			PlayersFinished++;
			Player->CrossedFinish();
			UE_LOG(LogTemp, Warning, TEXT("%i"), PlayersFinished);
			
			if (PlayersFinished == PlayersToStart)
			{
				UE_LOG(LogTemp, Warning, TEXT("Game Over"));
				Instance->Warp("EndLevel");
			}
		}
	}
}

void AMyGameStateBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMyGameStateBase, NumPlayers);
	DOREPLIFETIME(AMyGameStateBase, PlayersFinished);
}
