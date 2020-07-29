// Fill out your copyright notice in the Description page of Project Settings.
// �¶��� �⺻ ���� ��� 

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
	// ���ǿ� �������ִ� ���� ��� ��Ʈ�ѷ�
	UPROPERTY(replicated)
		TArray<APlayerController*> AllPlayerController;
};
