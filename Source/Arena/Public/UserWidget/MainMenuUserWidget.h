// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class ARENA_API UMainMenuUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;
private:
	UFUNCTION()
		void EditName_ChangedDelegateFuntion(const FText& Text);

	UFUNCTION()
		void CreateServerButton_OnClickedDelegateFuntion();

	UFUNCTION()
		void FindServerButton_OnClickedDelegateFuntion();

	UFUNCTION()
		void QuitGameButton_OnClickedDelegateFuntion();

private:
	UPROPERTY()
		class UEditableTextBox* EditNameTextBox;
	UPROPERTY()
		class UButton* CreateServerButton;
	UPROPERTY()
		class UButton* FindServerButton;
	UPROPERTY()
		class UButton* QuitGameButton;
};
