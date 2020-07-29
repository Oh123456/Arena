// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ServerListUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class ARENA_API UServerListUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	// ���� ã����� ȣ���ؼ� ��������Ʈ ����
	void RefreshServerList(TArray<FOnlineSessionSearchResult> SearchResults);

	void JoinServerDataSetting(FString ServerName, FOnlineSessionSearchResult* SearchResult );
	void Scroll_ChildWidgetButton_NormalTintColor_ZreoAlpha();
protected:
	virtual void NativeConstruct() override;

private:

	UFUNCTION()
		void RefreshServerListButton_ClickedDelegateFuntion();
	UFUNCTION()
		void JoinServerButton_ClickedDelegateFuntion();
	UFUNCTION()
		void BackButton_ClickedDelegateFuntion();
	UFUNCTION()
		void LANChickBox_CheckStateChangedDelegateFuntion(bool bIsChecked);

private:
	UPROPERTY()
		class UScrollBox* ServerListScrollBox;
	UPROPERTY()
		class UButton* RefreshServerListButton;
	UPROPERTY()
		class UButton* JoinServerButton;
	UPROPERTY()
		class UButton* BackButton;
	UPROPERTY()
		class UCheckBox* LANCheckBox;

	//���� ���� ����
private:
	bool bIsLAN;
	// ������ ����óġ ���
	FOnlineSessionSearchResult* FindSessionSearchResult;
	// ������ ���� �̸�
	FString FIndServerName;
};
