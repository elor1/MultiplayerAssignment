// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "PlayerCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
/**
 * 
 */
UCLASS()
class MULTIPLAYERGAME_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();


	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	void Respawn();

	void SetNewRespawnPoint();

	bool bHasFinished = false;
	
private:
	UPROPERTY(EditAnywhere)
	USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere)
	UCameraComponent* Camera;

	UPROPERTY(EditAnywhere)
	float LaunchSpeed = 1000;

	UPROPERTY(EditAnywhere)
	float MaxPushDistance = 100.0f;
	
	FVector StartLocation;

	void MoveForwards(float AxisValue);
	void Strafe(float AxisValue);
	void LookUp(float AxisValue);
	void Turn(float AxisValue);
	void Dive();
	void Push();
	void GetPushed(FVector Direction);

	UFUNCTION(Server, Reliable)
	void ServerDive();

	UFUNCTION(Server, Reliable)
	void ServerPush();

	UFUNCTION(Server, Reliable)
	void ServerGetPushed(FVector Direction);
};
