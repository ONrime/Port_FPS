// Fill out your copyright notice in the Description page of Project Settings.


#include "MultiPlayer_CharacterBase.h"
#include "Port_FPS/Character/Player/PlayerState/PlayerStateBase.h"
#include "Port_FPS/Character/Player/PlayerState/Aim_PlayerUpper_StateBase.h"
#include "Port_FPS/Character/Player/PlayerState/Standing_PlayerDown_StateBase.h"
#include "Port_FPS/Character/Player/PlayerState/MultiPlayer_State/Prone_M_PlayerDown_StateBase.h"

AMultiPlayer_CharacterBase::AMultiPlayer_CharacterBase()
{

}

void AMultiPlayer_CharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
	//SetStateDownN(NewObject<UProne_M_PlayerDown_StateBase>(this, UProne_M_PlayerDown_StateBase::StaticClass()));
	//GetStateDownN()->StateStart(this);
}

void AMultiPlayer_CharacterBase::TurnAtRate(float Rate)
{
	Super::TurnAtRate(Rate);
	GetStateDownN()->TurnAtRate(this, Rate);
}

void AMultiPlayer_CharacterBase::LookUpAtRate(float Rate)
{
	Super::LookUpAtRate(Rate);
	GetStateDownN()->LookUpAtRate(this, Rate);
}

void AMultiPlayer_CharacterBase::PlayerJump()
{
	Super::PlayerJump();
}

void AMultiPlayer_CharacterBase::MoveForward(float Value)
{
	Super::MoveForward(Value);
}

void AMultiPlayer_CharacterBase::MoveRight(float Value)
{
	Super::MoveRight(Value);
}

void AMultiPlayer_CharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMultiPlayer_CharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AMultiPlayer_CharacterBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}
