// Fill out your copyright notice in the Description page of Project Settings.


#include "SinglePlayer_CharacterBase.h"

ASinglePlayer_CharacterBase::ASinglePlayer_CharacterBase()
{

}

void ASinglePlayer_CharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

void ASinglePlayer_CharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASinglePlayer_CharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ASinglePlayer_CharacterBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}
