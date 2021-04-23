// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "Port_FPS/Character/Player/PlayerState/PlayerDown_StateBase.h"
#include "Standing_PlayerDown_StateBase.generated.h"

/**
 * 
 */
UCLASS()
class PORT_FPS_API UStanding_PlayerDown_StateBase : public UPlayerDown_StateBase
{
	GENERATED_BODY()
	
public:
	UStanding_PlayerDown_StateBase();
	virtual UPlayerDown_StateBase* HandleInput(class APlayer_CharacterBase* PlayerBase) override;
	virtual void StateStart(class APlayer_CharacterBase* PlayerBase) override;
	virtual void StateUpdate(class APlayer_CharacterBase* PlayerBase) override;
	virtual void StateEnd(class APlayer_CharacterBase* PlayerBase) override;
	virtual UClass* GetState() override;

	virtual void TurnAtRate(class APlayer_CharacterBase* PlayerBase, float Rate) override;

protected:

private:
	float PlayerRotationYawSpeed = 0.0f;
	float PlayerRotationYaw = 0.0f;

	FVector DodgeNowLoc = FVector::ZeroVector;
	FVector DodgeLoc = FVector::ZeroVector;
	FVector DodgeDir = FVector::ZeroVector;
	float DodgeLengh = 0.0f;
	bool CheckLoc(FVector now, FVector target, float min);
	FRotator SProneRot = FRotator::ZeroRotator;
	float SProneYaw = 0.0f;
	float CapsuleH = 0.0f;
	float MeshLocZ = 0.0f;

};
