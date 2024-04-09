// Liuxijun

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AuraUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	// BlueprintCallable指可以在蓝图中调用
	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UObject* InWidgetController);

	// 小部件控制器需要从蓝图访问
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UObject> WidgetController;

protected:
	// BlueprintImplementableEvent指在C++中声明，在蓝图中实现
	UFUNCTION(BlueprintImplementableEvent)
	void WidgetControllerSet();
};
