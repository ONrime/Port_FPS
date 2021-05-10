// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerDown_StateBase.h"

UPlayerDown_StateBase::UPlayerDown_StateBase()
{
	temp = nullptr;
}

UPlayerDown_StateBase* UPlayerDown_StateBase::HandleInput(APlayer_CharacterBase* PlayerBase)
{
	return nullptr;
}

void UPlayerDown_StateBase::StateStart(APlayer_CharacterBase* PlayerBase)
{
}

void UPlayerDown_StateBase::StateUpdate(APlayer_CharacterBase* PlayerBase)
{
}

void UPlayerDown_StateBase::StateEnd(APlayer_CharacterBase* PlayerBase)
{
}

UClass* UPlayerDown_StateBase::GetState()
{
	return UPlayerDown_StateBase::StaticClass();
}

void UPlayerDown_StateBase::TurnAtRate(APlayer_CharacterBase* PlayerBase, float Rate)
{

}

void UPlayerDown_StateBase::LookUpAtRate(APlayer_CharacterBase* PlayerBase, float Rate)
{
	if (PlayerBase->IsPlayerCameraTurn) {
		float PitchRate = Rate * PlayerBase->BaseLookUpRate * 0.008f;
		PlayerBase->AddControllerPitchInput(PitchRate);
	}
	else { // 카메라 움직임 끄기
		PlayerBase->SpringArm->bUsePawnControlRotation = false;
	}
}

void UPlayerDown_StateBase::MoveForward(APlayer_CharacterBase* PlayerBase, float Value)
{
}

void UPlayerDown_StateBase::MoveRight(APlayer_CharacterBase* PlayerBase, float Value)
{
}
