// Fill out your copyright notice in the Description page of Project Settings.


#include "MultiPlayer_CharacterBase.h"

AMultiPlayer_CharacterBase::AMultiPlayer_CharacterBase()
{

}

void AMultiPlayer_CharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

void AMultiPlayer_CharacterBase::TurnAtRate(float Rate)
{
	Super::TurnAtRate(Rate);
}

void AMultiPlayer_CharacterBase::LookUpAtRate(float Rate)
{
	Super::LookUpAtRate(Rate);
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
