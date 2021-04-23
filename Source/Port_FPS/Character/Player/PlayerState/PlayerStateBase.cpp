// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerStateBase.h"

UPlayerStateBase::UPlayerStateBase()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UPlayerStateBase::StateStart(APlayer_CharacterBase* PlayerBase)
{

}

void UPlayerStateBase::StateUpdate(APlayer_CharacterBase* PlayerBase)
{

}

void UPlayerStateBase::StateEnd(APlayer_CharacterBase* PlayerBase)
{

}

UClass* UPlayerStateBase::GetState()
{ return UPlayerStateBase::StaticClass(); }