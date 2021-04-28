
// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu_LevelScriptActor.h"
#include "GameInfo_Instance.h"

AMainMenu_LevelScriptActor::AMainMenu_LevelScriptActor()
{

}

void AMainMenu_LevelScriptActor::BeginPlay()
{
	auto GameIns = Cast<UGameInfo_Instance>(GetGameInstance());
	GameIns->Check_SaveGame();
}
