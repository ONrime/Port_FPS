// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Port_FPS/Character/Player/PlayerState/PlayerDown_StateBase.h"
#include "Crouch_PlayerDown_StateBase.generated.h"

/**
 * 
 */
UCLASS()
class PORT_FPS_API UCrouch_PlayerDown_StateBase : public UPlayerDown_StateBase
{
	GENERATED_BODY()
	
public:
	UCrouch_PlayerDown_StateBase();
	virtual UPlayerDown_StateBase* HandleInput(class APlayer_CharacterBase* PlayerBase) override;
	virtual void StateStart(class APlayer_CharacterBase* PlayerBase) override;
	virtual void StateUpdate(class APlayer_CharacterBase* PlayerBase) override;
	virtual void StateEnd(class APlayer_CharacterBase* PlayerBase) override;
	virtual UClass* GetState() override;

protected:

private:

};
