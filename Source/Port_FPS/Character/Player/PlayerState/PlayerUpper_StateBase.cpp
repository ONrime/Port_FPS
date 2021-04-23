// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerUpper_StateBase.h"

UPlayerUpper_StateBase::UPlayerUpper_StateBase() 
{
	temp = nullptr;
}

UPlayerUpper_StateBase* UPlayerUpper_StateBase::HandleInput(APlayer_CharacterBase* PlayerBase)
{
	return nullptr;
}

void UPlayerUpper_StateBase::StateStart(APlayer_CharacterBase* PlayerBase)
{
}

void UPlayerUpper_StateBase::StateUpdate(APlayer_CharacterBase* PlayerBase)
{
}

void UPlayerUpper_StateBase::StateEnd(APlayer_CharacterBase* PlayerBase)
{
}

UClass* UPlayerUpper_StateBase::GetState()
{
	return UPlayerUpper_StateBase::StaticClass();
}
