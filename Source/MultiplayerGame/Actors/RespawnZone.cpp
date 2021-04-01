// Fill out your copyright notice in the Description page of Project Settings.


#include "RespawnZone.h"
#include "Components/BoxComponent.h"
#include "MultiplayerGame/Pawns/PlayerCharacter.h"

// Sets default values
ARespawnZone::ARespawnZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Setup trigger box
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger Box"));
	RootComponent = CollisionBox;
	CollisionBox->SetBoxExtent(FVector(1000.0f, 1000.0f, 1000.0f));
	CollisionBox->SetCollisionProfileName("Trigger");
}

// Called when the game starts or when spawned
void ARespawnZone::BeginPlay()
{
	Super::BeginPlay();

	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ARespawnZone::OnOverlapBegin);
}

// Called every frame
void ARespawnZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARespawnZone::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Fell out of world"));
	APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor);
	if (Player)
	{
		Player->Respawn();
	}
}

