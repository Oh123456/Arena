// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "UserWidget.h"
#include "BaseHUD.generated.h"

/**
 * 
 */
UCLASS()
class ARENA_API ABaseHUD : public AHUD
{
	GENERATED_BODY()

public:
	ABaseHUD();

	virtual void BeginPlay() override;

	UUserWidget* GetChattingWidget() const { return ChattingWidget; }
	TSubclassOf<UUserWidget> GetChattingWidgetClass() const { return ChattingWidgetClass; }
	TSubclassOf<UUserWidget> GetChattingLogWidgetClass() const { return ChattingLogWidgetClass; }
private:

	// Ã¤ÆÃ À§Á¬
	UUserWidget* ChattingWidget;

	TSubclassOf<UUserWidget> ChattingWidgetClass;
	TSubclassOf<UUserWidget> ChattingLogWidgetClass;
};
