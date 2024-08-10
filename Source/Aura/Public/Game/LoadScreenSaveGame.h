// Liuxijun

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "LoadScreenSaveGame.generated.h"

UENUM(BlueprintType)
enum ESaveSlotStatus
{
	Vacant,
	EnterName,
	Taken
};

/**
 * 
 */
UCLASS()
class AURA_API ULoadScreenSaveGame : public USaveGame
{
	GENERATED_BODY()

public:

	// 保存数据时，必须通过名称和索引来指定要保存的内容
	UPROPERTY()
	FString SlotName = FString();

	UPROPERTY()
	int32 SlotIndex;

	UPROPERTY()
	FString MapName = FString("Default Map Name");

	// 防止两个Slot使用相同的PlayerName
	UPROPERTY()
	FString PlayerName = FString("Default Name");

	UPROPERTY()
	TEnumAsByte<ESaveSlotStatus> SaveSlotStatus = Vacant;
};
