// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "GeneratedCodeHelpers.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/GameModeBase.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Setup spring arm
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->SetRelativeLocation(FVector(0.0f, 10.0f, 75.0f));
	SpringArm->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
	SpringArm->TargetArmLength = 250.0f;
	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed = 5.0f;
	SpringArm->bEnableCameraRotationLag = true;
	SpringArm->CameraRotationLagSpeed = 5.0f;

	//Setup camera
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation();
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	FHitResult OutHit;
	GetCharacterMovement()->SafeMoveUpdatedComponent(FVector(0.0f, 0.0f, 0.01f), GetActorRotation(), true, OutHit);
	GetCharacterMovement()->SafeMoveUpdatedComponent(FVector(0.0f, 0.0f, -0.01f), GetActorRotation(), true, OutHit);
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForwards"), this, &APlayerCharacter::MoveForwards);
	PlayerInputComponent->BindAxis(TEXT("Strafe"), this, &APlayerCharacter::Strafe);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APlayerCharacter::LookUp);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &APlayerCharacter::Turn);
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Dive"), EInputEvent::IE_Pressed, this, &APlayerCharacter::Dive);
	PlayerInputComponent->BindAction(TEXT("Push"), EInputEvent::IE_Pressed, this, &APlayerCharacter::Push);
}

void APlayerCharacter::MoveForwards(float AxisValue)
{
	AddMovementInput(GetActorForwardVector() * AxisValue);
}

void APlayerCharacter::Strafe(float AxisValue)
{
	AddMovementInput(GetActorRightVector() * AxisValue);
}

void APlayerCharacter::LookUp(float AxisValue)
{
	AddControllerPitchInput(AxisValue);
}

void APlayerCharacter::Turn(float AxisValue)
{
	AddControllerYawInput(AxisValue);
}

void APlayerCharacter::Dive()
{
	ServerDive();
}

void APlayerCharacter::Push()
{
	ServerPush();
}

void APlayerCharacter::GetPushed(FVector Direction)
{
	ServerGetPushed(Direction);
}

void APlayerCharacter::ClientPlayWinSound_Implementation()
{
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), WinSound, GetActorLocation());
}

void APlayerCharacter::ServerGetPushed_Implementation(FVector Direction)
{
	LaunchCharacter(Direction * LaunchSpeed, false, false);
}

void APlayerCharacter::ServerPush_Implementation()
{
	FVector PlayerPosition = GetActorLocation();
	FVector EndPoint = PlayerPosition + GetActorForwardVector() * MaxPushDistance;

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	FHitResult Hit;
	bool bSuccess = GetWorld()->LineTraceSingleByChannel(Hit, PlayerPosition, EndPoint, ECollisionChannel::ECC_GameTraceChannel1, Params);
	if (bSuccess)
	{
		APlayerCharacter* OtherPlayer = Cast<APlayerCharacter>(Hit.GetActor());
		if (OtherPlayer)
		{
			OtherPlayer->GetPushed(GetActorForwardVector());
		}
	}
}

void APlayerCharacter::ServerDive_Implementation()
{
	LaunchCharacter(GetActorForwardVector() * LaunchSpeed, false, false);
}

void APlayerCharacter::Respawn()
{
	SetActorLocation(StartLocation);
}

void APlayerCharacter::SetNewRespawnPoint()
{
	FVector PlayerPosition = GetActorLocation();
	if (PlayerPosition.Y < StartLocation.Y)
	{
		StartLocation = PlayerPosition;
	}
}

void APlayerCharacter::CrossedFinish()
{
	bHasFinished = true;
	ClientPlayWinSound();
}
