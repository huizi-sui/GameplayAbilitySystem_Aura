// Liuxijun

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "HighlightInterface.generated.h"

// This class does not need to be modified.
// 可以直接在蓝图中设置继承接口
UINTERFACE(MinimalAPI, BlueprintType)
class UHighlightInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class AURA_API IHighlightInterface
{
	GENERATED_BODY()

public:
	
	// 当鼠标悬停在敌人上方时，突出显示敌人
	UFUNCTION(BlueprintNativeEvent)
	void HighlightActor();
	UFUNCTION(BlueprintNativeEvent)
	void UnHighlightActor();

	UFUNCTION(BlueprintNativeEvent)
	void SetMoveToLocation(FVector& OutDestination);
};
