// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Port_FPS/Character/Player/Player_CharacterBase.h"
#include "PlayerStateBase.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PORT_FPS_API UPlayerStateBase : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerStateBase();

	virtual void StateStart(class APlayer_CharacterBase* PlayerBase);
	virtual void StateUpdate(class APlayer_CharacterBase* PlayerBase);
	virtual void StateEnd(class APlayer_CharacterBase* PlayerBase);
	virtual UClass* GetState();

protected:

public:	
		
};
