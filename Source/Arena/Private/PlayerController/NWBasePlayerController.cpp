// Fill out your copyright notice in the Description page of Project Settings.

#include "NWBasePlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "NWGameModeBase.h"
#include "UnrealNetwork.h"

#include "NWGameInstance.h"
#include "ChattingUserWidget.h"
#include "BaseHUD.h"

ANWBasePlayerController::ANWBasePlayerController()
{

}

void ANWBasePlayerController::GetLifetimeReplicatedProps(TArray< class FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ANWBasePlayerController, ChattingText);
}

void ANWBasePlayerController::BeginPlay()
{
	Super::BeginPlay();
	ANWGameModeBase* NWGameMode = Cast<ANWGameModeBase>(UGameplayStatics::GetGameMode(Cast<UObject>(GetWorld())));
	NWGameMode->AddPlayerController(this);
}

bool ANWBasePlayerController::ChattingLogUpdate_Validate(const FText& Text)
{
	if (Text.IsEmpty())
		return false;
	return true;
}

void ANWBasePlayerController::ChattingLogUpdate_Implementation(const FText& Text)
{
	ANWGameModeBase* NWGameMode = Cast<ANWGameModeBase>(UGameplayStatics::GetGameMode(Cast<UObject>(GetWorld())));
	TArray<APlayerController*> PlayerController = NWGameMode->GetAllPlayerController();
	ChattingText = Text;
	int32 PlayerMax = PlayerController.Num();
	for (int32 i = 0; i < PlayerMax; i++)
	{
		ANWBasePlayerController* NWController = Cast<ANWBasePlayerController>(PlayerController.GetData()[i]);
		if (NWController)
			NWController->UPdateMassge(ChattingText);
	}

}

void ANWBasePlayerController::UPdateMassge_Implementation(const FText& Text)
{
	ABaseHUD* BaseHUD = Cast<ABaseHUD>(this->GetHUD());
	UChattingUserWidget* ChattingWidget = Cast<UChattingUserWidget>(BaseHUD->GetChattingWidget());
	UNWGameInstance* NWGameInstance = Cast<UNWGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	ChattingWidget->UpdateChattingLog(NWGameInstance->GetPlayerInfo()->PlayerName, Text);
}