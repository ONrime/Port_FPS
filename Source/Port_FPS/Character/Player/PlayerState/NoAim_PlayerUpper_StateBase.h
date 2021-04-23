// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Port_FPS/Character/Player/PlayerState/PlayerUpper_StateBase.h"
#include "NoAim_PlayerUpper_StateBase.generated.h"

/**
 * 
 */
UCLASS()
class PORT_FPS_API UNoAim_PlayerUpper_StateBase : public UPlayerUpper_StateBase
{
	GENERATED_BODY()
	
public:
	UNoAim_PlayerUpper_StateBase();
	virtual UPlayerUpper_StateBase* HandleInput(class APlayer_CharacterBase* PlayerBase) override;
	virtual void StateStart(class APlayer_CharacterBase* PlayerBase) override;
	virtual void StateUpdate(class APlayer_CharacterBase* PlayerBase) override;
	virtual void StateEnd(class APlayer_CharacterBase* PlayerBase) override;
	virtual UClass* GetState() override;

protected:

private:

};
