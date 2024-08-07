// Liuxijun

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AuraUserWidget.generated.h"

/**
 *	MVC模式
 *  Widget需要知道Widget Controller是谁，向Widget Controller绑定事件。
 *  当Widget Controller感知到Model中的数据发生变化（例如需要显示在HUD上的Attribute Set中的属性），会广播数据，
 *  这时Widget的事件就会被触发。
 *
 *  通过函数SetWidgetController设置此Widget的Widget Controller，当设置后，就可以向Widget Controller绑定事件，
 *  调用WidgetControllerSet()函数，该函数被声明为在蓝图中实现，这样可以根据不同的Widget设置各自的需要绑定的内容。
 */
UCLASS()
class AURA_API UAuraUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UObject* InWidgetController);
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UObject> WidgetController;

protected:

	UFUNCTION(BlueprintImplementableEvent)
	void WidgetControllerSet();
};
