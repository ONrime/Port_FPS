// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Port_FPS/Character/Player/PlayerState/PlayerStateBase.h"
#include "PlayerUpper_StateBase.generated.h"

/**
 * 
 */
UCLASS()
class PORT_FPS_API UPlayerUpper_StateBase : public UPlayerStateBase
{
	GENERATED_BODY()

public:
	UPlayerUpper_StateBase();
	virtual UPlayerUpper_StateBase* HandleInput(class APlayer_CharacterBase* PlayerBase);
	virtual void StateStart(class APlayer_CharacterBase* PlayerBase) override;
	virtual void StateUpdate(class APlayer_CharacterBase* PlayerBase) override;
	virtual void StateEnd(class APlayer_CharacterBase* PlayerBase) override;
	virtual UClass* GetState() override;

protected:
	UPROPERTY(VisibleAnywhere, Category = State)
	class UPlayerUpper_StateBase* temp;

private:

	
};
