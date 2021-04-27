// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Port_FPS/CustomStructs.h"
#include "PlayerInfo_SaveGame.generated.h"

/**
 * 
 */
UCLASS()
class PORT_FPS_API UPlayerInfo_SaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	UPlayerInfo_SaveGame();

	UPROPERTY(Replicated)
	FPlayerInfo S_PlayerInfo;

protected:

private:

};
