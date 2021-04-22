// Fill out your copyright notice in the Description page of Project Settings.


#include "FinishZone.h"
#include "Components/BoxComponent.h"
#include "Niagara/Public/NiagaraComponent.h"
#include "Components/TextRenderComponent.h"
#include "Kismet/GameplayStatics.h"
#include "MultiplayerGame/MultiplayerGameGameModeBase.h"
#include "MultiplayerGame/Pawns/PlayerCharacter.h"

// Sets default values
AFinishZone::AFinishZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Setup static mesh
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;
	
	//Setup trigger box
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger Box"));
	CollisionBox->SetupAttachment(Mesh);
	CollisionBox->SetBoxExtent(FVector(100.0f, 100.0f, 100.0f));
	CollisionBox->SetCollisionProfileName("Trigger");

	//Set up particle systems
	Particle1 = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Particle 1"));
	Particle1->SetPaused(true);
	Particle2 = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Particle 2"));
	Particle1->SetPaused(false);

	//Set up text
	Text = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Text"));
	Text->SetupAttachment(Mesh);
	Text->SetText(FText::FromString(TEXT("FINISH")));
	Text->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));
}

// Called when the game starts or when spawned
void AFinishZone::BeginPlay()
{
	Super::BeginPlay();

	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AFinishZone::OnOverlapBegin);
}

// Called every frame
void AFinishZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFinishZone::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (HasAuthority())
	{
		if (APlayerCharacter* Player = Cast<APlayerCharacter>(OtherActor))
		{
			if (!Player->bHasFinished)
			{
				UE_LOG(LogTemp, Warning, TEXT("Finish"));
				AGameModeBase* GameMode = UGameplayStatics::GetGameMode(GetWorld());
				if (GameMode)
				{
					AMultiplayerGameGameModeBase* ModeBase = Cast<AMultiplayerGameGameModeBase>(GameMode);
					if (ModeBase)
					{
						ModeBase->PlayerFinished(Player);
					}
				}

				if (Particle1->IsPaused())
				{
					Particle1->SetPaused(false);
				}
				if (Particle2->IsPaused())
				{
					Particle2->SetPaused(false);
				}
			}
		}
	}
}

