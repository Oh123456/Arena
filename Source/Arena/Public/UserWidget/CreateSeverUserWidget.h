// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CreateSeverUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class ARENA_API UCreateSeverUserWidget : public UUserWidget
{
	GENERATED_BODY()
	

protected:
	virtual void NativeConstruct() override;
private:
	UFUNCTION()
		void EditServerName_ChangedDelegateFuntion(const FText& Text);
	UFUNCTION()
		void EditMaxPlayer_ChangedDelegateFuntion(const FText& Text);
	UFUNCTION()
		void CreateButton_OnClickedDelegateFuntion();
	UFUNCTION()
		void BackButton_OnClickedDelegateFuntion();
	UFUNCTION()
		void LANChickBox_CheckStateChangedDelegateFuntion(bool bIsChecked);
private:
	UPROPERTY()
		class UEditableTextBox* EditServerNameTextBox;
	UPROPERTY()
		class UEditableTextBox* EditMaxPlayerTextBox;
	UPROPERTY()
		class UButton* CreateButton;
	UPROPERTY()
		class UButton* BackButton;
	UPROPERTY()
		class UCheckBox* LANChickBox;

private:
	FText ServerName;
	int32 nMaxPlayer;
	bool bIsLAN;
};
