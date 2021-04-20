// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"

void UMyGameInstance::Host()
{
	UWorld* World = GetWorld();
	if (World)
	{
		World->ServerTravel("/Game/Maps/HoldingLevel?listen");
	}
}

void UMyGameInstance::Join(const FString IPAddress)
{
	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (PlayerController)
	{
		UE_LOG(LogTemp, Warning, TEXT("Joining %s"), *IPAddress);
		PlayerController->ClientTravel(IPAddress, ETravelType::TRAVEL_Absolute);
	}
}

void UMyGameInstance::Warp(const FString LevelName)
{
	UWorld* World = GetWorld();
	if (World)
	{
		FString Destination = FString::Printf(TEXT("/Game/Maps/%s?listen"), *LevelName);
		World->ServerTravel(Destination);
	}
}
