// Fill out your copyright notice in the Description page of Project Settings.
// 온라인 기본 게임 모드 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "NWGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class ARENA_API ANWGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ANWGameModeBase();
	
	inline void AddPlayerController(APlayerController* PController) { AllPlayerController.Add(PController); }

	inline TArray<APlayerController*> GetAllPlayerController() const { return AllPlayerController; }


	virtual void GetLifetimeReplicatedProps(TArray< class FLifetimeProperty > & OutLifetimeProps) const;
private:
	// 세션에 접속해있는 게임 모드 컨트롤러
	UPROPERTY(replicated)
		TArray<APlayerController*> AllPlayerController;
};
