// Fill out your copyright notice in the Description page of Project Settings.

#include "GameInstance/NWGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "OnlineSubsystem.h"
#include "Engine/World.h"


UNWGameInstance::UNWGameInstance()
{

}


void UNWGameInstance::Init()
{
	Super::Init();
	IOnlineSubsystem* OnlineSubsysyem = IOnlineSubsystem::Get();
	if (OnlineSubsysyem)
	{
		SessionInterface = OnlineSubsysyem->GetSessionInterface();
		if (SessionInterface.IsValid())
		{
			// 델리게이트 바인드
			SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UNWGameInstance::OnCreateSessionComplete);
			SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UNWGameInstance::OnFindSessionsComplete);
			SessionInterface->OnJoinSessionCompleteDelegates.AddUObject(this, &UNWGameInstance::OnJoinSessionComplete);
		}
	}
}

void UNWGameInstance::OnCreateSessionComplete(FName SeverName, bool Succeeded)
{
	UE_LOG(LogTemp, Warning, TEXT("OnCreateSessionComplete, Succeeded: %d") , Succeeded);
	if (Succeeded)
	{
		// 시작맵?
		GetWorld()->ServerTravel("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen");
	}
}

void UNWGameInstance::OnFindSessionsComplete(bool Succeeded)
{
	UE_LOG(LogTemp, Warning, TEXT("OnFindSessionsComplete, Succeeded: %d"), Succeeded);
	if (Succeeded)
	{
		TArray<FOnlineSessionSearchResult> SearchResults = SessionSearch->SearchResults;
		UE_LOG(LogTemp, Warning, TEXT("SearchResults, ServerCount: %d"), SearchResults.Num());
		// 세션 조건 걸기
		if (SearchResults.Num())
		{
			UE_LOG(LogTemp, Warning, TEXT("JoinServer"));
			SessionInterface->JoinSession(0, FName("My Server"), SearchResults[0]);
		}
	}
}

void UNWGameInstance::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
	UE_LOG(LogTemp, Warning, TEXT("OnJoinSessionComplete SessionName: %s") , *SessionName.ToString());
	APlayerController* PController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PController)
	{
		FString JoinAddress; 
		SessionInterface->GetResolvedConnectString(SessionName, JoinAddress);
		if (JoinAddress != "")
			PController->ClientTravel(JoinAddress, ETravelType::TRAVEL_Absolute);
	}
}

void UNWGameInstance::CreateServer(FName ServerName, bool bIsLAN, int MaxPlayer)
{
	UE_LOG(LogTemp, Warning, TEXT("CreateServer"));


	FOnlineSessionSettings SessionSesttings;

	SessionSesttings.bAllowJoinInProgress = true;
	SessionSesttings.bIsDedicated = false;
	SessionSesttings.bIsLANMatch = bIsLAN;
	SessionSesttings.bShouldAdvertise = true;
	SessionSesttings.bUsesPresence = true;
	SessionSesttings.NumPublicConnections = MaxPlayer;
	


	SessionInterface->CreateSession(0, ServerName, SessionSesttings);
}


void UNWGameInstance::JoinServer()
{

	SessionSearch = MakeShareable(new FOnlineSessionSearch());
	SessionSearch->bIsLanQuery = true; // 렌모드
	SessionSearch->MaxSearchResults = 10; // 찾는갯수
	SessionSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);

	SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
}

