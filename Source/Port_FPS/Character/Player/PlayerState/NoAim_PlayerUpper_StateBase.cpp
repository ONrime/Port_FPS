// Fill out your copyright notice in the Description page of Project Settings.


#include "NoAim_PlayerUpper_StateBase.h"
#include "Port_FPS/Character/Player/PlayerState/Aim_PlayerUpper_StateBase.h"
#include "GameFramework/PlayerInput.h"
#include "GameFramework/PlayerController.h"

UNoAim_PlayerUpper_StateBase::UNoAim_PlayerUpper_StateBase()
{

}

UPlayerUpper_StateBase* UNoAim_PlayerUpper_StateBase::HandleInput(APlayer_CharacterBase* PlayerBase)
{
	auto PlayerController = Cast<APlayerController>(PlayerBase->GetController());
	auto PlayerInput = Cast<UPlayerInput>(PlayerController->PlayerInput);
	TArray < FInputActionKeyMapping > ActionNoAim = PlayerInput->GetKeysForAction(TEXT("NoAim"));

	if (PlayerInput->IsPressed(ActionNoAim[0].Key)) {
		temp = NewObject<UAim_PlayerUpper_StateBase>(this, UAim_PlayerUpper_StateBase::StaticClass());
	}
	return temp;
}

void UNoAim_PlayerUpper_StateBase::StateStart(APlayer_CharacterBase* PlayerBase)
{
}

void UNoAim_PlayerUpper_StateBase::StateUpdate(APlayer_CharacterBase* PlayerBase)
{
}

void UNoAim_PlayerUpper_StateBase::StateEnd(APlayer_CharacterBase* PlayerBase)
{
}

UClass* UNoAim_PlayerUpper_StateBase::GetState()
{
	return UNoAim_PlayerUpper_StateBase::StaticClass();
}
