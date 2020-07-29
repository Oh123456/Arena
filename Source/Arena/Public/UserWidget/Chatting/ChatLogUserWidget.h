// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ChatLogUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class ARENA_API UChatLogUserWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void SetChattingLog(FText PlayerName, FText ChattingLog);

protected:
	virtual void NativeConstruct() override;

private:
	UPROPERTY()
		class UTextBlock* NameTextBlock;
	UPROPERTY()
		class UTextBlock* ChattingLogTextBlock;
};
