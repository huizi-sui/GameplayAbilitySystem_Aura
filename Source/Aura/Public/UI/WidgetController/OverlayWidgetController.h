// Liuxijun

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "OverlayWidgetController.generated.h"

// 创建代表来传播这些数值
// 动态多播代表： 1. 想要在蓝图中将事件分配给它们，特别是小部件蓝图
// 因为有多个蓝图，多个小部件蓝图，所以希望是动态多播的，可能想要绑定到这些委托以便它们可以更新。

// 只想要传递一个值，所以OneParam
// 这只是声明
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignature, float, NewHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxHealthChangedSignature, float, NewMaxHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnManaChangedSignature, float, NewMana);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FonMaxManaChangedSignature, float, NewMaxMana);

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
	FOnHealthChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attribute")
	FOnMaxHealthChangedSignature OnMaxHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attribute")
	FOnManaChangedSignature OnManaChanged;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attribute")
	FonMaxManaChangedSignature OnMaxManaChanged;

protected:
	// 它必须绑定到能力系统组件上的哪些委托的签名
	void HealthChanged(const FOnAttributeChangeData& Data) const;
	void MaxHealthChanged(const FOnAttributeChangeData& Data) const;
	void ManaChanged(const FOnAttributeChangeData& Data) const;
	void MaxManaChanged(const FOnAttributeChangeData& Data) const;
};
