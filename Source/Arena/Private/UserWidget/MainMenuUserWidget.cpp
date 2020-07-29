// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenuUserWidget.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

#include "GameInstance/NWGameInstance.h"


void UMainMenuUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	EditNameTextBox = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("Name_EditableTextBox")));
	if (EditNameTextBox)
		EditNameTextBox->OnTextChanged.AddDynamic(this, &UMainMenuUserWidget::EditName_ChangedDelegateFuntion);
	CreateServerButton = Cast<UButton>(GetWidgetFromName(TEXT("Create_Button")));
	if (CreateServerButton)
		CreateServerButton->OnClicked.AddDynamic(this, &UMainMenuUserWidget::CreateServerButton_OnClickedDelegateFuntion);
	FindServerButton = Cast<UButton>(GetWidgetFromName(TEXT("FindServer_Button")));
	if (FindServerButton)
		FindServerButton->OnClicked.AddDynamic(this, &UMainMenuUserWidget::FindServerButton_OnClickedDelegateFuntion);
	QuitGameButton = Cast<UButton>(GetWidgetFromName(TEXT("QuitGame_Button")));
	if (QuitGameButton)
		QuitGameButton->OnClicked.AddDynamic(this, &UMainMenuUserWidget::QuitGameButton_OnClickedDelegateFuntion);
}

void UMainMenuUserWidget::EditName_ChangedDelegateFuntion(const FText& Text)
{
	UNWGameInstance* NWGameInstance = Cast<UNWGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	NWGameInstance->GetPlayerInfo()->PlayerName = Text;
}


void UMainMenuUserWidget::CreateServerButton_OnClickedDelegateFuntion()
{
	UNWGameInstance* NWGameInstance = Cast<UNWGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	NWGameInstance->ShowCreateSverMenu();
	this->RemoveFromParent();
}

void UMainMenuUserWidget::FindServerButton_OnClickedDelegateFuntion()
{
	UNWGameInstance* NWGameInstance = Cast<UNWGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	NWGameInstance->ShowServerList();
	this->RemoveFromParent();
}

void UMainMenuUserWidget::QuitGameButton_OnClickedDelegateFuntion()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), GetOwningPlayer(), EQuitPreference::Quit, true);
}