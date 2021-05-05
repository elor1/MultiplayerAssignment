// Fill out your copyright notice in the Description page of Project Settings.


#include "SlidingDoor.h"

#include "GeneratedCodeHelpers.h"

ASlidingDoor::ASlidingDoor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;
}

// Called when the game starts or when spawned
void ASlidingDoor::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		NetUpdateFrequency = 1;
		SetReplicates(true);
		SetReplicateMovement(true);
		Speed = FMath::RandRange(MinSpeed, MaxSpeed);
		SlideState = (ESlideState)FMath::RandRange(1, 2);
		MaxHeight = GetActorLocation().Z;
		CurrentHeight = MaxHeight;
	}
}

void ASlidingDoor::SetStateDown_Implementation()
{
	SlideState = ESlideState::Down;
}

void ASlidingDoor::SetStateUp_Implementation()
{
	SlideState = ESlideState::Up;
}

void ASlidingDoor::SetStatePaused_Implementation()
{
	SlideState = ESlideState::Pause;
}

// Called every frame
void ASlidingDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (SlideState == ESlideState::Down)
	{
		SetActorLocation(FVector(GetActorLocation().X, GetActorLocation().Y, FMath::Max(GetActorLocation().Z - Speed * DeltaTime, MinHeight)));
		CurrentHeight -= Speed * DeltaTime;
	}
	else if (SlideState == ESlideState::Up)
	{
		SetActorLocation(FVector(GetActorLocation().X, GetActorLocation().Y, FMath::Min(GetActorLocation().Z + Speed * DeltaTime, MaxHeight)));
		CurrentHeight += Speed * DeltaTime;
	}

	if (HasAuthority())
	{
		if (CurrentHeight <= MinHeight)
		{
			if (SlideState == ESlideState::Pause)
			{
				if (!GetWorldTimerManager().IsTimerActive(PauseTimer))
				{
					float RandomTime = FMath::RandRange(MinPauseTime, MaxPauseTime);
					GetWorldTimerManager().SetTimer(PauseTimer, this, &ASlidingDoor::SetStateUp, RandomTime, false);
				}
			}
			else
			{
				SetStatePaused();
			}
		}
		else if (CurrentHeight >= MaxHeight)
		{
			if (SlideState == ESlideState::Pause)
			{
				if (!GetWorldTimerManager().IsTimerActive(PauseTimer))
				{
					float RandomTime = FMath::RandRange(MinPauseTime, MaxPauseTime);
					GetWorldTimerManager().SetTimer(PauseTimer, this, &ASlidingDoor::SetStateDown, RandomTime, false);
				}
			}
			else
			{
				SetStatePaused();
			}
		}
	}
}

void ASlidingDoor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(ASlidingDoor, Speed, COND_InitialOnly);
	DOREPLIFETIME_CONDITION(ASlidingDoor, MaxHeight, COND_InitialOnly);
	DOREPLIFETIME_CONDITION(ASlidingDoor, CurrentHeight, COND_InitialOnly);
	DOREPLIFETIME_CONDITION(ASlidingDoor, SlideState, COND_InitialOnly);
}