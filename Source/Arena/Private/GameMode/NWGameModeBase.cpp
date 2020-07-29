// Fill out your copyright notice in the Description page of Project Settings.

#include "NWGameModeBase.h"
#include "UnrealNetwork.h"

ANWGameModeBase::ANWGameModeBase()
{

}

void ANWGameModeBase::GetLifetimeReplicatedProps(TArray< class FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ANWGameModeBase, AllPlayerController);
}