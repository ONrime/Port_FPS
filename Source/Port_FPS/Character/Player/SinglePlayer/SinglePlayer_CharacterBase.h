// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "Port_FPS/Character/Player/Player_CharacterBase.h"
#include "SinglePlayer_CharacterBase.generated.h"

/**
 * 
 */
UCLASS()
class PORT_FPS_API ASinglePlayer_CharacterBase : public APlayer_CharacterBase
{
	GENERATED_BODY()

public:
	ASinglePlayer_CharacterBase();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void PostInitializeComponents() override;

private:

	
};
