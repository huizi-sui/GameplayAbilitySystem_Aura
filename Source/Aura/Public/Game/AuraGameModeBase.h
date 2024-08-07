// Liuxijun

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "AuraGameModeBase.generated.h"

class UAbilityInfo;
class UCharacterClassInfo;

/**
 * 
 */
UCLASS()
class AURA_API AAuraGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:

	// 游戏中各种角色的一些属性、能力等，在UAuraAbilitySystemLibrary::InitializeDefaultAttributes函数中初始化各个角色相关信息
	UPROPERTY(EditDefaultsOnly, Category = "Character Class Defaults")
	TObjectPtr<UCharacterClassInfo> CharacterClassInfo;

	UPROPERTY(EditDefaultsOnly, Category = "Abiltiy Info")
	TObjectPtr<UAbilityInfo> AbilityInfo;
};
