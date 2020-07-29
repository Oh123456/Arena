// Fill out your copyright notice in the Description page of Project Settings.

#include "GameInstance/NWGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/World.h"
#include "OnlineSubsystem.h"
#include "UnrealNetwork.h"

#include "ServerListUserWidget.h" 


UNWGameInstance::UNWGameInstance() 
{
	static ConstructorHelpers::FClassFinder<UUserWidget> MAINMENU(TEXT("/Game/MainMenu/UI/MainMenuWidgetBlueprint.MainMenuWidgetBlueprint_C")); 
	if (MAINMENU.Succeeded())
	{
		MainMenuWidgetClass = MAINMENU.Class;
	}
	static ConstructorHelpers::FClassFinder<UUserWidget> SERVERLIST(TEXT("/Game/MainMenu/UI/ServerListWidgetBlueprint.ServerListWidgetBlueprint_C"));
	if (SERVERLIST.Succeeded())
	{
		ServerListWidgetClass = SERVERLIST.Class;
	}
	static ConstructorHelpers::FClassFinder<UUserWidget> CREATESERVERMENU(TEXT("/Game/MainMenu/UI/CreateServerWidgetBlueprint.CreateServerWidgetBlueprint_C"));
	if (CREATESERVERMENU.Succeeded())
	{
		CreateSverMenuWidgetClass = CREATESERVERMENU.Class;
	}
	static ConstructorHelpers::FClassFinder<UUserWidget> SERVERUSERWIDGET(TEXT("/Game/MainMenu/UI/ServerWidgetBlueprint.ServerWidgetBlueprint_C"));
	if (SERVERUSERWIDGET.Succeeded())
	{
		ServerUserWidgetClass = SERVERUSERWIDGET.Class;
	}

}

UNWGameInstance::~UNWGameInstance()
{
	//SessionInterface->DestroySession(CreateServerName);
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

void UNWGameInstance::GetLifetimeReplicatedProps(TArray< class FLifetimeProperty > & OutLifetimeProps) const 
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UNWGameInstance, PlayerInfo);
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
		//TArray<FOnlineSessionSearchResult> 
		//if (SessionSearch.IsValid() == false)
		//	return;
		SearchResults = SessionSearch->SearchResults;
		UE_LOG(LogTemp, Warning, TEXT("SearchResults, ServerCount: %d"), SearchResults.Num());
		FString JoinAddress;

		// UMG 테스트에서 사용할 변수 차후 CPP로 변경할경우 삭제

		ServerNames.Empty();
		// 세션 조건 걸기
		for (int32 i = 0; i < SearchResults.Num(); i++)
		{
			FString ServerName;
			SearchResults[i].Session.SessionSettings.Get(SETTING_SERVER_NAME, ServerName);
			UE_LOG(LogTemp, Warning, TEXT("SearchResults, ServerName: %s"), *ServerName);
			ServerNames.Add(ServerName);


			// UMG 테스트에서 사용할 변수 차후 CPP로 변경할경우 삭제
			FBlueprintSessionResult BP_SessionResult;
			BP_SessionResult.OnlineResult = SearchResults[i];

		}
		
	
		UServerListUserWidget* ServerListWidget = Cast<UServerListUserWidget>(CreatedUserWidget);
		if (ServerListWidget)
			ServerListWidget->RefreshServerList(SearchResults);
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


	FOnlineSessionSettings SessionSettings;

	SessionSettings.bAllowJoinInProgress = true;
	SessionSettings.bIsDedicated = false;
	SessionSettings.bIsLANMatch = bIsLAN;
	SessionSettings.bShouldAdvertise = true;
	SessionSettings.bUsesPresence = true;
	SessionSettings.NumPublicConnections = MaxPlayer;
	
	FOnlineSessionSetting ExtraSessionSetting;
	ExtraSessionSetting.AdvertisementType = EOnlineDataAdvertisementType::ViaOnlineService;

	//setting the temporary data to the ServerName we got from UMG
	ExtraSessionSetting.Data = ServerName.ToString();

	//adding the Server Name value in the FOnlineSessionSetting 's settings array using the key defined in header
	//the key can be any FNAME but we define it to avoid mistakes
	SessionSettings.Settings.Add(SETTING_SERVER_NAME, ExtraSessionSetting);

	/*
					비밀번호 할시 주석 해제

	//setting the temporary data to the bIsPasswordProtected we got from UMG
	ExtraSessionSetting.Data = bIsPasswordProtected;
	//adding the bIsPasswordProtected value in the FOnlineSessionSetting 's settings array using the key defined in header
	SessionSettings->Settings.Add(SETTING_SERVER_IS_PROTECTED, ExtraSessionSetting);


	//setting the temporary data to the Password we got from UMG
	ExtraSessionSetting.Data = SessionPassword;
	//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, *ExtraSessionSetting.Data.ToString());
	//adding the Password value in the FOnlineSessionSetting 's settings array using the key defined in header
	SessionSettings->Settings.Add(SETTING_SERVER_PROTECT_PASSWORD, ExtraSessionSetting);
	
	*/
	CreateServerName = ServerName;
	SessionInterface->CreateSession(0, ServerName, SessionSettings);
}


void UNWGameInstance::JoinServer(int32 PlayerNum, FName SessionName, const FOnlineSessionSearchResult& SearchResult)
{
	UE_LOG(LogTemp, Warning, TEXT("JoinServer %d"), SearchResult.Session.NumOpenPublicConnections);
	SessionInterface->JoinSession(PlayerNum, SessionName, SearchResult);
}


// 세션 찾기 최대수
const int8 MaxSearchSessionResults = 10;

void UNWGameInstance::FindServer(bool bIsLAN)
{
	SessionSearch = MakeShareable(new FOnlineSessionSearch());
	SessionSearch->bIsLanQuery = bIsLAN; // 렌모드
	SessionSearch->MaxSearchResults = MaxSearchSessionResults; // 찾는갯수
	SessionSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);

	SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
}


void UNWGameInstance::ShowMainMenu()
{
	UUserWidget* MainMenuWidget = CreateWidget<UUserWidget>(GetWorld(), MainMenuWidgetClass);
	MainMenuWidget->AddToViewport();
	CreatedUserWidget = MainMenuWidget;
}

void UNWGameInstance::ShowServerList()
{
	UUserWidget* ServerListWidget = CreateWidget<UUserWidget>(GetWorld(), ServerListWidgetClass);
	ServerListWidget->AddToViewport();
	CreatedUserWidget = ServerListWidget;
}

void UNWGameInstance::ShowCreateSverMenu()
{
	UUserWidget* CreateSverMenuWidget = CreateWidget<UUserWidget>(GetWorld(), CreateSverMenuWidgetClass);
	CreateSverMenuWidget->AddToViewport();
	CreatedUserWidget = CreateSverMenuWidget;
}