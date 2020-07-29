// Fill out your copyright notice in the Description page of Project Settings.

#include "CreateSeverUserWidget.h"
#include "Components/CheckBox.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetStringLibrary.h"
#include "Kismet/KismetTextLibrary.h"

#include "GameInstance/NWGameInstance.h"

void UCreateSeverUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	EditServerNameTextBox = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("ServerName_EditableTextBox")));
	if (EditServerNameTextBox)
		EditServerNameTextBox->OnTextChanged.AddDynamic(this, &UCreateSeverUserWidget::EditServerName_ChangedDelegateFuntion);
	EditMaxPlayerTextBox = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("MaxPlayer_EditableTextBox")));
	if (EditMaxPlayerTextBox)
		EditMaxPlayerTextBox->OnTextChanged.AddDynamic(this, &UCreateSeverUserWidget::EditMaxPlayer_ChangedDelegateFuntion);
	CreateButton = Cast<UButton>(GetWidgetFromName(TEXT("Create_Button1")));
	if (CreateButton)
		CreateButton->OnClicked.AddDynamic(this , &UCreateSeverUserWidget::CreateButton_OnClickedDelegateFuntion);
	BackButton = Cast<UButton>(GetWidgetFromName(TEXT("Back_Button_1")));
	if (BackButton)
		BackButton->OnClicked.AddDynamic(this, &UCreateSeverUserWidget::BackButton_OnClickedDelegateFuntion);
	LANChickBox = Cast<UCheckBox>(GetWidgetFromName(TEXT("LANMode_CheckBox")));
	if (LANChickBox)
		LANChickBox->OnCheckStateChanged.AddDynamic(this , &UCreateSeverUserWidget::LANChickBox_CheckStateChangedDelegateFuntion);

	bIsLAN = false;
	nMaxPlayer = 1;
}


void UCreateSeverUserWidget::EditServerName_ChangedDelegateFuntion(const FText& Text)
{
	ServerName = FText();
	ServerName = Text;
}

void UCreateSeverUserWidget::EditMaxPlayer_ChangedDelegateFuntion(const FText& Text)
{
	nMaxPlayer = UKismetStringLibrary::Conv_StringToInt(Text.ToString());
	if (nMaxPlayer <= 0)
	{
		nMaxPlayer = 1;
		EditMaxPlayerTextBox->SetText(UKismetTextLibrary::Conv_IntToText(nMaxPlayer));
	}
	if (nMaxPlayer >= 20)
	{
		nMaxPlayer = 20;
		EditMaxPlayerTextBox->SetText(UKismetTextLibrary::Conv_IntToText(nMaxPlayer));
	}

}

void UCreateSeverUserWidget::CreateButton_OnClickedDelegateFuntion()
{
	UNWGameInstance* NWGameInstance = Cast<UNWGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	
	NWGameInstance->CreateServer(UKismetStringLibrary::Conv_StringToName(ServerName.ToString()), bIsLAN, nMaxPlayer);
}

void UCreateSeverUserWidget::BackButton_OnClickedDelegateFuntion()
{
	UNWGameInstance* NWGameInstance = Cast<UNWGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	NWGameInstance->ShowMainMenu();
	this->RemoveFromParent();
}

void UCreateSeverUserWidget::LANChickBox_CheckStateChangedDelegateFuntion(bool bIsChecked)
{
	bIsLAN = bIsChecked;
}