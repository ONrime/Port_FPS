// Fill out your copyright notice in the Description page of Project Settings.


#include "Prone_M_PlayerDown_StateBase.h"
#include "Port_FPS/Character/Player/PlayerState/Standing_PlayerDown_StateBase.h"
#include "Port_FPS/Character/Player/PlayerState/Crouch_PlayerDown_StateBase.h"
#include "Port_FPS/Character/Player/MultiPlayer/MultiPlayer_CharacterBase.h"
#include "GameFramework/PlayerInput.h"
#include "GameFramework/PlayerController.h"

UProne_M_PlayerDown_StateBase::UProne_M_PlayerDown_StateBase()
{

}

UPlayerDown_StateBase* UProne_M_PlayerDown_StateBase::HandleInput(APlayer_CharacterBase* PlayerBase)
{
	auto PlayerController = Cast<APlayerController>(PlayerBase->GetController());
	auto PlayerInput = Cast<UPlayerInput>(PlayerController->PlayerInput);
	TArray < FInputActionKeyMapping > ActionCrouch = PlayerInput->GetKeysForAction(TEXT("Crouch"));

	if (PlayerInput->IsPressed(ActionCrouch[0].Key)) {
		temp = NewObject<UStanding_PlayerDown_StateBase>(this, UStanding_PlayerDown_StateBase::StaticClass());
	}
	return temp;
}

void UProne_M_PlayerDown_StateBase::StateStart(APlayer_CharacterBase* PlayerBase)
{
	/*auto MPlayer = Cast<AMultiPlayer_CharacterBase>(PlayerBase);
	UE_LOG(LogTemp, Warning, TEXT("UProne_M_PlayerDown: Start"));*/
}

void UProne_M_PlayerDown_StateBase::StateUpdate(APlayer_CharacterBase* PlayerBase)
{
}

void UProne_M_PlayerDown_StateBase::StateEnd(APlayer_CharacterBase* PlayerBase)
{
}

UClass* UProne_M_PlayerDown_StateBase::GetState()
{
	return nullptr;
}
