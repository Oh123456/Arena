// Fill out your copyright notice in the Description page of Project Settings.

#include "ChattingUserWidget.h"
#include "Components/EditableText.h"
#include "Components/ScrollBox.h"

#include "BaseHUD.h"
#include "ChatLogUserWidget.h"
#include "NWBasePlayerController.h"

void UChattingUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ChattinEditableText = Cast<UEditableText>(GetWidgetFromName(TEXT("Chat_EditableText")));
	ChattinEditableText->OnTextCommitted.AddDynamic(this, &UChattingUserWidget::Chatting_TextCommittedDelegateFuntion);
	ChattingLogScroll = Cast<UScrollBox>(GetWidgetFromName(TEXT("ChatLog_ScrollBox")));
}

void UChattingUserWidget::Chatting_TextCommittedDelegateFuntion(const FText& Text, ETextCommit::Type CommitMethod)
{
	if (CommitMethod == ETextCommit::Type::OnEnter)
	{
		ANWBasePlayerController* PController = Cast<ANWBasePlayerController>(GetOwningPlayer());
		PController->ChattingLogUpdate(Text);
	}
}

void UChattingUserWidget::UpdateChattingLog_Implementation(const FText& PlayerName, const FText& ChattingLog)
{
	ABaseHUD* BaseHUD = Cast<ABaseHUD>(GetOwningPlayer()->GetHUD());

	UUserWidget* Create = CreateWidget<UUserWidget>(GetWorld(), BaseHUD->GetChattingLogWidgetClass());
	UChatLogUserWidget* ChatLogWidget = Cast<UChatLogUserWidget>(Create);
	ChattingLogScroll->AddChild(ChatLogWidget);
	ChatLogWidget->SetChattingLog(PlayerName, ChattingLog);
	ChattingLogScroll->ScrollToEnd();
}