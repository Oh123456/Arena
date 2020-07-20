// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "OnlineSessionSettings.h"
#include "OnlineSubsystem.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "NWGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class ARENA_API UNWGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UNWGameInstance();

protected:
	virtual void Init() override;

	virtual void OnCreateSessionComplete(FName SeverName, bool Succeeded);
	virtual void OnFindSessionsComplete(bool Succeeded);
	virtual void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);

	UFUNCTION(BlueprintCallable)
		void CreateServer(FName ServerName = FName("My Server"), bool bIsLAN = true, int MaxPlayer = 5);

	UFUNCTION(BlueprintCallable)
		void JoinServer();

protected:
	IOnlineSessionPtr SessionInterface;

	TSharedPtr<FOnlineSessionSearch> SessionSearch;
};
