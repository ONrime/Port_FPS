// Fill out your copyright notice in the Description page of Project Settings.


#include "Crouch_PlayerDown_StateBase.h"
#include "Port_FPS/Character/Player/PlayerState/Standing_PlayerDown_StateBase.h"
#include "GameFramework/PlayerInput.h"
#include "GameFramework/PlayerController.h"

UCrouch_PlayerDown_StateBase::UCrouch_PlayerDown_StateBase() 
{

}

UPlayerDown_StateBase* UCrouch_PlayerDown_StateBase::HandleInput(APlayer_CharacterBase* PlayerBase)
{
	auto PlayerController = Cast<APlayerController>(PlayerBase->GetController());
	auto PlayerInput = Cast<UPlayerInput>(PlayerController->PlayerInput);
	TArray < FInputActionKeyMapping > ActionCrouch = PlayerInput->GetKeysForAction(TEXT("Crouch"));

	if (PlayerInput->IsPressed(ActionCrouch[0].Key)) {
		temp = NewObject<UStanding_PlayerDown_StateBase>(this, UStanding_PlayerDown_StateBase::StaticClass());
	}
	return temp;
}

void UCrouch_PlayerDown_StateBase::StateStart(APlayer_CharacterBase* PlayerBase)
{
	UE_LOG(LogTemp, Warning, TEXT("UCrouch_PlayerDown: Start"));
}

void UCrouch_PlayerDown_StateBase::StateUpdate(APlayer_CharacterBase* PlayerBase)
{
}

void UCrouch_PlayerDown_StateBase::StateEnd(APlayer_CharacterBase* PlayerBase)
{
}

UClass* UCrouch_PlayerDown_StateBase::GetState()
{
	return UCrouch_PlayerDown_StateBase::StaticClass();
}
