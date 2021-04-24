// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "Port_FPS/Character/Player/Player_CharacterBase.h"
#include "MultiPlayer_CharacterBase.generated.h"

/**
 * 
 */
UCLASS()
class PORT_FPS_API AMultiPlayer_CharacterBase : public APlayer_CharacterBase
{
	GENERATED_BODY()

public:
	AMultiPlayer_CharacterBase();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AloowPrivateAccess = "true"))
	class USkeletalMeshComponent* BodyMesh;

	/*UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AloowPrivateAccess = "true"))
		class USkeletalMeshComponent* GunMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AloowPrivateAccess = "true"))
		class USkeletalMeshComponent* BodyMesh;*/

protected:
	virtual void BeginPlay() override;
	virtual void TurnAtRate(float Rate) override;
	virtual void LookUpAtRate(float Rate) override;
	virtual void PlayerJump() override;
	virtual void MoveForward(float Value) override;
	virtual void MoveRight(float Value) override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void PostInitializeComponents() override;

private:

	
};
