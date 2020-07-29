// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "NWBasePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class ARENA_API ANWBasePlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ANWBasePlayerController();

	UFUNCTION(Server, Reliable, WithValidation)
		void ChattingLogUpdate(const FText& Text);
		bool ChattingLogUpdate_Validate(const FText& Text);
		void ChattingLogUpdate_Implementation(const FText& Text);
	UFUNCTION(Client, Reliable)
		void UPdateMassge(const FText& Text);
		void UPdateMassge_Implementation(const FText& Text);
	virtual void GetLifetimeReplicatedProps(TArray< class FLifetimeProperty > & OutLifetimeProps) const;
	virtual void BeginPlay() override;


private:
	UPROPERTY(replicated)
		FText ChattingText;
};
