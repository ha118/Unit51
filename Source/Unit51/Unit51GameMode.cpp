// Copyright Epic Games, Inc. All Rights Reserved.

#include "Unit51GameMode.h"
#include "Unit51HUD.h"
#include "Unit51Character.h"
#include "UObject/ConstructorHelpers.h"

AUnit51GameMode::AUnit51GameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AUnit51HUD::StaticClass();
}
