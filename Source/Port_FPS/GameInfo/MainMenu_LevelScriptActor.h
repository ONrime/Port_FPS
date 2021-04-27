// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "MainMenu_LevelScriptActor.generated.h"

/**
 * 
 */
UCLASS()
class PORT_FPS_API AMainMenu_LevelScriptActor : public ALevelScriptActor
{
	GENERATED_BODY()
	
public:
	AMainMenu_LevelScriptActor();

protected:
	virtual void BeginPlay() override;

};
