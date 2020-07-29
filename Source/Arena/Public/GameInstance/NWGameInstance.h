// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "OnlineSessionSettings.h"
#include "OnlineSubsystem.h"
#include "FindSessionsCallbackProxy.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "UserWidget.h"
#include "NWGameInstance.generated.h"

#define SETTING_SERVER_NAME FName(TEXT("SERVERNAMEKEY"))


USTRUCT(BlueprintType)
struct FPlayerInfo
{
	GENERATED_BODY()
public:
	FText PlayerName;
	class ACharacter* PlayerCharacter;

};


/**
 * 
 */
UCLASS()
class ARENA_API UNWGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UNWGameInstance(); 
	~UNWGameInstance();

	void SetJoinServerName(FString str) { JoinServerName = str; }
	FString GetJoinServerName() { return JoinServerName; }


	UFUNCTION(BlueprintCallable)
		FText PlayerName() { return PlayerInfo.PlayerName; }

	FPlayerInfo* GetPlayerInfo() { return &PlayerInfo; }
	TArray<FOnlineSessionSearchResult> GetSearchResults() { return SearchResults; }

	virtual void GetLifetimeReplicatedProps(TArray< class FLifetimeProperty > & OutLifetimeProps) const;
public:
	void ShowMainMenu();
	void ShowServerList();
	void ShowCreateSverMenu();
	UUserWidget* CreateServerUserWidget() { return CreateWidget<UUserWidget>(GetWorld(), ServerUserWidgetClass); }
private:
	TSubclassOf<UUserWidget> MainMenuWidgetClass;
	TSubclassOf<UUserWidget> ServerListWidgetClass;
	TSubclassOf<UUserWidget> CreateSverMenuWidgetClass;
	TSubclassOf<UUserWidget> ServerUserWidgetClass;

	UUserWidget* CreatedUserWidget;
public:

	
	void CreateServer(FName ServerName = FName("My Server"), bool bIsLAN = true, int MaxPlayer = 5);
	void JoinServer(int32 PlayerNum, FName SessionName, const FOnlineSessionSearchResult& SearchResult);
	void FindServer(bool bIsLAN = true);

protected:
	virtual void Init() override;

	virtual void OnCreateSessionComplete(FName SeverName, bool Succeeded);
	virtual void OnFindSessionsComplete(bool Succeeded);
	virtual void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);


protected:
	IOnlineSessionPtr SessionInterface;

	TSharedPtr<FOnlineSessionSearch> SessionSearch;
	
	TArray<FOnlineSessionSearchResult> SearchResults;



	UPROPERTY(BlueprintReadOnly)
		TArray<FString> ServerNames;


private:
	UPROPERTY(replicated)
		FPlayerInfo PlayerInfo;
	// 참여 중인 서버이름 혹은 참여할려는 서버 이름
	FString JoinServerName;

	FName CreateServerName;
};