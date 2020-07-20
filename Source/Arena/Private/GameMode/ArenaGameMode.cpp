// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "GameMode/ArenaGameMode.h"
#include "Character/ArenaCharacter.h"
#include "UObject/ConstructorHelpers.h"

AArenaGameMode::AArenaGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
