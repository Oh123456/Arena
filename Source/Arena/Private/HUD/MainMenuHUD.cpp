
#include "MainMenuHUD.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"

#include "NWGameInstance.h"



void AMainMenuHUD::BeginPlay()
{
	Super::BeginPlay();

	UNWGameInstance* NWGameInstance = Cast<UNWGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	NWGameInstance->ShowMainMenu();

	APlayerController* PController = GetOwningPlayerController();
	PController->bShowMouseCursor = true;
	PController->SetInputMode(FInputModeUIOnly());
}