

#include "UserWidget/ServerUserWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Styling/SlateBrush.h"
#include "Styling/SlateTypes.h"
#include "Styling/SlateColor.h"
#include "Color.h"

#include "NWGameInstance.h"
#include "ServerListUserWidget.h"


void UServerUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ServerIndexButton = Cast<UButton>(GetWidgetFromName(TEXT("ServerList_Button_0")));
	if (ServerIndexButton)
		ServerIndexButton->OnClicked.AddDynamic(this, &UServerUserWidget::ServerIndexButton_ClickedDelegateFuntion);
	ServerIndexNameTextBlock = Cast<UTextBlock>(GetWidgetFromName(TEXT("ServerIndex_ServerName_TextBlock_2")));
	ServerIndexPingTextBlock = Cast<UTextBlock>(GetWidgetFromName(TEXT("ServerIndex_ServerPing_TextBlock_2")));
	ServerIndexPlayerCountTextBlock = Cast<UTextBlock>(GetWidgetFromName(TEXT("ServerIndex_ServerPlayerCount_TextBlock_2")));
	

}

void UServerUserWidget::ServerIndexButton_ClickedDelegateFuntion()
{
	
	// GetParent가 널포인터이다.. 이유를 모르겠다
	//UServerListUserWidget* ParentWidget = Cast<UServerListUserWidget>(GetParent());

	//if (ParentWidget)
	//	ParentWidget->Scroll_ChildWidgetButton_NormalTintColor_ZreoAlpha();
	//ServerIndexButton->WidgetStyle.Normal.TintColor = FSlateColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));

	//if (SessionSearchResult)
	//{
	//	FString ServerName = ServerIndexNameTextBlock->GetText().ToString();
	//	ParentWidget->JoinServerDataSetting(ServerName, SessionSearchResult);
	//	GameInstance->SetJoinServerName(ServerName);
	//}

	UNWGameInstance* GameInstance = Cast<UNWGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	UServerListUserWidget* ParentWidget = Cast<UServerListUserWidget>(ParentScrollBoxWodget);
	ParentWidget->Scroll_ChildWidgetButton_NormalTintColor_ZreoAlpha();

	ServerIndexButton->WidgetStyle.Normal.TintColor = FSlateColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));

	if (SessionSearchResult)
	{
		FString ServerName = ServerIndexNameTextBlock->GetText().ToString();
		ParentWidget->JoinServerDataSetting(ServerName, SessionSearchResult);
		GameInstance->SetJoinServerName(ServerName);
	}
}

void UServerUserWidget::ServerIndexButton_NormalTintColor_ZreoAlpha() 
{
	ServerIndexButton->WidgetStyle.Normal.TintColor = FSlateColor(FLinearColor(1.0f, 1.0f, 1.0f, 0.0f)); 
}

void UServerUserWidget::SetServerIndexNameText(FText& Text)
{
	ServerIndexNameTextBlock->SetText(Text);
}

void UServerUserWidget::SetServerIndexPingText(FText& Text)
{ 
	ServerIndexPingTextBlock->SetText(Text);
}

void UServerUserWidget::SetServerIndexPlayerCountText(FText& Text)
{
	ServerIndexPlayerCountTextBlock->SetText(Text);
}