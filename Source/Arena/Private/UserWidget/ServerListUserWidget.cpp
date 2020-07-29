

#include "ServerListUserWidget.h"
#include "Components/ScrollBox.h"
#include "Components/Button.h"
#include "Components/CheckBox.h"
#include "Components/TextBlock.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/VerticalBoxSlot.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetTextLibrary.h"
#include "Kismet/KismetStringLibrary.h"

#include "NWGameInstance.h"
#include "ServerUserWidget.h"


void UServerListUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ServerListScrollBox = Cast<UScrollBox>(GetWidgetFromName(TEXT("ServerList_ScrollBox")));
	RefreshServerListButton = Cast<UButton>(GetWidgetFromName(TEXT("RefreshServerList_Button")));
	if (RefreshServerListButton)
		RefreshServerListButton->OnClicked.AddDynamic(this, &UServerListUserWidget::RefreshServerListButton_ClickedDelegateFuntion);
	UServerListUserWidget::RefreshServerListButton_ClickedDelegateFuntion();
	
	JoinServerButton = Cast<UButton>(GetWidgetFromName(TEXT("JoinServer_Button_1")));
	if(JoinServerButton)
		JoinServerButton->OnClicked.AddDynamic(this, &UServerListUserWidget::JoinServerButton_ClickedDelegateFuntion);
	BackButton = Cast<UButton>(GetWidgetFromName(TEXT("Back_Button_2")));
	if (BackButton)
		BackButton->OnClicked.AddDynamic(this, &UServerListUserWidget::BackButton_ClickedDelegateFuntion);
	LANCheckBox = Cast<UCheckBox>(GetWidgetFromName(TEXT("LANMode_CheckBox")));
	if (LANCheckBox)
		LANCheckBox->OnCheckStateChanged.AddDynamic(this, &UServerListUserWidget::LANChickBox_CheckStateChangedDelegateFuntion);

	bIsLAN = false;
}

void UServerListUserWidget::RefreshServerList(TArray<FOnlineSessionSearchResult> SearchResults)
{
	UE_LOG(LogTemp, Warning, TEXT("RefreshServerList, ServerCount: %d"), SearchResults.Num());
	ServerListScrollBox->ClearChildren();
	UNWGameInstance* GameInstance = Cast<UNWGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	int32 ResultsMax = SearchResults.Num();
	for (int32 i = 0; i < ResultsMax; i++ )
	{
		UServerUserWidget* ServerWidget = Cast<UServerUserWidget>(GameInstance->CreateServerUserWidget());
		if (ServerWidget )
		{
			

			UPanelSlot* Child = ServerListScrollBox->AddChild(ServerWidget);

			FString ServerName(L"TEST");
			SearchResults.GetData()[i].Session.SessionSettings.Get(SETTING_SERVER_NAME, ServerName);
			FText ServerNameText = UKismetTextLibrary::Conv_StringToText(ServerName);
			ServerWidget->SetServerIndexNameText(ServerNameText);
			UE_LOG(LogTemp, Warning, TEXT("RefreshServerNAME_END"));

			int32 PlayerCount = SearchResults.GetData()[i].Session.NumOpenPublicConnections;
			int32 MaxPlayer = SearchResults.GetData()[i].Session.SessionSettings.NumPublicConnections;
			FString PlaterCount_Text = FString::FromInt(PlayerCount);
			FString MaxPlayer_Text = FString::FromInt(MaxPlayer);
			FString ResultStr = UKismetStringLibrary::Concat_StrStr(PlaterCount_Text, L" / ");
			ResultStr = UKismetStringLibrary::Concat_StrStr(ResultStr, MaxPlayer_Text);
			FText Resulttext = UKismetTextLibrary::Conv_StringToText(ResultStr);
			ServerWidget->SetServerIndexPlayerCountText(Resulttext);
			UE_LOG(LogTemp, Warning, TEXT("RefreshServerPlayerCount_END"));

			int32 Ping = SearchResults.GetData()[i].PingInMs;
			FText PingText = UKismetTextLibrary::Conv_IntToText(Ping);
			ServerWidget->SetServerIndexPingText(PingText);
			UE_LOG(LogTemp, Warning, TEXT("RefreshServerPING_END"));


			ServerWidget->SetSessionSearchResult(&SearchResults.GetData()[i]);
			ServerWidget->SetParentScrollBoxWodget(this);
			//UHorizontalBoxSlot* HorBox = Cast<UHorizontalBoxSlot>(Child);
			//HorBox->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Fill);

			//UVerticalBoxSlot* VerBox = Cast<UVerticalBoxSlot>(Child);
			//VerBox->SetVerticalAlignment(EVerticalAlignment::VAlign_Fill);
		}
			
	}
	UE_LOG(LogTemp, Warning, TEXT("RefreshServerList_END"));
}

void UServerListUserWidget::Scroll_ChildWidgetButton_NormalTintColor_ZreoAlpha()
{
	if (this == nullptr)
		return;
	int32 MaxChild = ServerListScrollBox->GetChildrenCount();
	for (int32 i = 0; i < MaxChild; i++)
	{
		UServerUserWidget* Child = Cast<UServerUserWidget>(ServerListScrollBox->GetChildAt(i));
		Child->ServerIndexButton_NormalTintColor_ZreoAlpha();
	}
}

void UServerListUserWidget::JoinServerDataSetting(FString ServerName, FOnlineSessionSearchResult* SearchResult)
{
	FIndServerName.Empty();
	FIndServerName = ServerName;
	FindSessionSearchResult = nullptr;
	FindSessionSearchResult = SearchResult;
}

void UServerListUserWidget::RefreshServerListButton_ClickedDelegateFuntion()
{
	UNWGameInstance* GameInstance = Cast<UNWGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	GameInstance->FindServer(bIsLAN);
	FindSessionSearchResult = nullptr;
	UServerListUserWidget::Scroll_ChildWidgetButton_NormalTintColor_ZreoAlpha();
}

void UServerListUserWidget::JoinServerButton_ClickedDelegateFuntion()
{
	if (FindSessionSearchResult)
	{
		UNWGameInstance* GameInstance = Cast<UNWGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
		GameInstance->JoinServer(0, UKismetStringLibrary::Conv_StringToName(FIndServerName), *FindSessionSearchResult);
	}
}

void UServerListUserWidget::BackButton_ClickedDelegateFuntion()
{
	UNWGameInstance* NWGameInstance = Cast<UNWGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	NWGameInstance->ShowMainMenu();
	this->RemoveFromParent();
}

void UServerListUserWidget::LANChickBox_CheckStateChangedDelegateFuntion(bool bIsChecked)
{
	bIsLAN = bIsChecked;
}