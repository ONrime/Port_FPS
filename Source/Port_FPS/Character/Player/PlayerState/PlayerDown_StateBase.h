// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Port_FPS/Character/Player/PlayerState/PlayerStateBase.h"
#include "PlayerDown_StateBase.generated.h"

/**
 * 
 */
UCLASS()
class PORT_FPS_API UPlayerDown_StateBase : public UPlayerStateBase
{
	GENERATED_BODY()
	
public:
	UPlayerDown_StateBase();
	virtual UPlayerDown_StateBase* HandleInput(class APlayer_CharacterBase* PlayerBase);
	virtual void StateStart(class APlayer_CharacterBase* PlayerBase) override;
	virtual void StateUpdate(class APlayer_CharacterBase* PlayerBase) override;
	virtual void StateEnd(class APlayer_CharacterBase* PlayerBase) override;
	virtual UClass* GetState() override;

	virtual void TurnAtRate(class APlayer_CharacterBase* PlayerBase, float Rate);
	virtual void LookUpAtRate(class APlayer_CharacterBase* PlayerBase, float Rate);
	virtual void MoveForward(class APlayer_CharacterBase* PlayerBase, float Value);
	virtual void MoveRight(class APlayer_CharacterBase* PlayerBase, float Value);

protected:
	UPROPERTY(VisibleAnywhere, Category = State)
	class UPlayerDown_StateBase* temp;

private:


};
