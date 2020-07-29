// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OnlineSessionSettings.h"
#include "Components/Button.h"
#include "ServerUserWidget.generated.h"

/**
 * 
 */




UCLASS()
class ARENA_API UServerUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void ServerListSetting(TArray<FOnlineSessionSearchResult> SearchResults);

	void SetServerIndexNameText(FText& Text);
	void SetServerIndexPingText(FText& Text); 
	void SetServerIndexPlayerCountText(FText& Text); 
	void SetSessionSearchResult(FOnlineSessionSearchResult* SearchResult) { SessionSearchResult = SearchResult; }
	inline void SetParentScrollBoxWodget(UUserWidget* Widget) { ParentScrollBoxWodget = Widget; }

	void ServerIndexButton_NormalTintColor_ZreoAlpha();// { ServerIndexButton->WidgetStyle.Normal.TintColor = FSlateColor(FLinearColor(1.0f, 1.0f, 1.0f, 0.0f)); };
protected:
	virtual void NativeConstruct() override;

private:
	UFUNCTION()
		void ServerIndexButton_ClickedDelegateFuntion();

private:
	UPROPERTY()
		UButton* ServerIndexButton;
public:
	UPROPERTY()
		class UTextBlock* ServerIndexNameTextBlock;
	UPROPERTY()
		class UTextBlock* ServerIndexPingTextBlock;
	UPROPERTY()
		class UTextBlock* ServerIndexPlayerCountTextBlock;
private:
	// 세션 정보
	FOnlineSessionSearchResult* SessionSearchResult;

	UUserWidget* ParentScrollBoxWodget;
};
