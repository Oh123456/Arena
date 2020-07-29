// Fill out your copyright notice in the Description page of Project Settings.

#include "ChatLogUserWidget.h"
#include "Components/TextBlock.h"



void UChatLogUserWidget::NativeConstruct()
{
	Super::NativeConstruct();


	NameTextBlock = Cast<UTextBlock>(GetWidgetFromName(TEXT("ChatLogNameTextBlock_123")));
	ChattingLogTextBlock = Cast<UTextBlock>(GetWidgetFromName(TEXT("ChatLogChattingTextBlock_123")));
}

void UChatLogUserWidget::SetChattingLog(FText PlayerName, FText ChattingLog)
{
	NameTextBlock->SetText(PlayerName);  
	ChattingLogTextBlock->SetText(ChattingLog); 
}
