// Liuxijun

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "OverlayWidgetController.generated.h"

// 创建代表来传播这些数值
// 动态多播代表： 1. 想要在蓝图中将事件分配给它们，特别是小部件蓝图
// 因为有多个蓝图，多个小部件蓝图，所以希望是动态多播的，可能想要绑定到这些委托以便它们可以更新。

struct FAuraAbilityInfo;

USTRUCT(BlueprintType)
struct FUIWidgetRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag MessageTag = FGameplayTag();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Message = FText();

	// 在这个数据表中，想要一个可以在屏幕上显示的小部件类
	// 所以对于任意给定的游戏标签，都可以创建一个小部件并将其添加到视口中
	// 我们以游戏效果的形式表示收到了该游戏标签
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<class UAuraUserWidget> MessageWidget;

	// 可选的图像
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTexture2D* Image = nullptr;
};

class UAuraUserWidget;
class UAuraAbilitySystemComponent;
class UAbilityInfo;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeChangedSignature, float, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMessageWidgetRowSignature, FUIWidgetRow, Row);


/**
 * 
 */
// BlueprintType：我们可以做一些事情，例如将它用作事件图中的类型
// Buleprintable：我们可以基于这个类制作一个蓝图
UCLASS(BlueprintType, Blueprintable)
class AURA_API UOverlayWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()

public:
	
	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;

	// 希望在蓝图中分配它们
	UPROPERTY(BlueprintAssignable, Category = "GAS|Attribute")
	FOnAttributeChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attribute")
	FOnAttributeChangedSignature OnMaxHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attribute")
	FOnAttributeChangedSignature OnManaChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attribute")
	FOnAttributeChangedSignature OnMaxManaChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attribute")
	FMessageWidgetRowSignature MessageWidgetRowDelegate;

	UPROPERTY(BlueprintAssignable, Category = "GAS|XP")
	FOnAttributeChangedSignature OnXPPercentChangedDelegate;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Level")
	FOnPlayerStateChangedSignature OnPlayerLevelChangedDelegate;

protected:

	// 希望能够从小部件控制器的蓝图中设置它
	// 我们只会编辑默认值
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Widget Data")
	TObjectPtr<UDataTable> MessageWidgetDataTable;

	// 根据标签去数据表中查找任意类型的一行数据
	template<typename T>
	T* GetDataRowByTag(UDataTable* DataTable, const FGameplayTag& Tag);

	void OnXPChanged(int32 NewXP);

	void OnAbilityEquipped(const FGameplayTag& AbilityTag, const FGameplayTag& Status, const FGameplayTag& Slot, const FGameplayTag& PreviousSlot) const;
};

template <typename T>
T* UOverlayWidgetController::GetDataRowByTag(UDataTable* DataTable, const FGameplayTag& Tag)
{
	// 第二个参数ContextString没有任何作用
	return DataTable->FindRow<T>(Tag.GetTagName(), TEXT(""));
}
