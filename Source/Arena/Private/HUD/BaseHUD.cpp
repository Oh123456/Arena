// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseHUD.h"
#include "UObject/ConstructorHelpers.h"

ABaseHUD::ABaseHUD()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> CHATTING(TEXT("/Game/ChattingUI/ChattingWidgetBlueprint.ChattingWidgetBlueprint_C"));
	if (CHATTING.Succeeded())
	{
		ChattingWidgetClass = CHATTING.Class;
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> CHATTINGLOG(TEXT("/Game/ChattingUI/ChatLogWidgetBlueprint.ChatLogWidgetBlueprint_C"));
	if (CHATTINGLOG.Succeeded())
	{
		ChattingLogWidgetClass = CHATTINGLOG.Class;
	}
}


void ABaseHUD::BeginPlay()
{
	Super::BeginPlay();
	ChattingWidget = CreateWidget<UUserWidget>(GetWorld(), ChattingWidgetClass);
	ChattingWidget->AddToViewport();
}