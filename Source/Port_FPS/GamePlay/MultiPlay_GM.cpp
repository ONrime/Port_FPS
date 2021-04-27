// Fill out your copyright notice in the Description page of Project Settings.


#include "MultiPlay_GM.h"
#include "Port_FPS/Character/Player/MultiPlayer/MultiPlayer_CharacterBase.h"
#include "Port_FPS/GamePlay/MultiPlay_PC.h"

AMultiPlay_GM::AMultiPlay_GM()
{
	DefaultPawnClass = AMultiPlayer_CharacterBase::StaticClass();
	PlayerControllerClass = AMultiPlay_PC::StaticClass();
}