// Copyright Epic Games, Inc. All Rights Reserved.

#include "Port_FPSGameMode.h"
#include "Port_FPSHUD.h"
#include "Port_FPSCharacter.h"
#include "UObject/ConstructorHelpers.h"

APort_FPSGameMode::APort_FPSGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = APort_FPSHUD::StaticClass();
}
