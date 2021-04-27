// Fill out your copyright notice in the Description page of Project Settings.


#include "Loby_GM.h"
#include "Port_FPS/Character/Player/MultiPlayer/MultiPlayer_CharacterBase.h"
#include "Port_FPS/Loby/Loby_PC.h"

ALoby_GM::ALoby_GM() 
{
	DefaultPawnClass = AMultiPlayer_CharacterBase::StaticClass();
	PlayerControllerClass = ALoby_PC::StaticClass();
}