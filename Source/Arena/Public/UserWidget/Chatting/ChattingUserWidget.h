// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ChattingUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class ARENA_API UChattingUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// 스크롤 박스에 채팅로그 업데이트
	UFUNCTION(Client, Reliable)
		void UpdateChattingLog(const FText& PlayerName, const FText& ChattingLog);
		void UpdateChattingLog_Implementation(const FText& PlayerName, const FText& ChattingLog);
protected:
	virtual void NativeConstruct() override;
private:
	UFUNCTION()
		void Chatting_TextCommittedDelegateFuntion(const FText& Text, ETextCommit::Type CommitMethod);
private:
	UPROPERTY()
		class UEditableText* ChattinEditableText;
	UPROPERTY()
		class UScrollBox* ChattingLogScroll;
};
