// Liuxijun

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "EnemyInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UEnemyInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class AURA_API IEnemyInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	// 当鼠标悬停在敌人上方时，突出显示敌人
	virtual void HighlightActor() = 0;
	virtual void UnHighlightActor() = 0;

	// 1. 蓝图可调用函数 2. 蓝图中实现这些功能
	// 实现这两个目标的方法是制作一个蓝图Native事件
	// 虽然是非virtual，但是会为我们自动生成一个可以覆盖的虚拟函数
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SetCombatTarget(AActor* InCombatTarget);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	AActor* GetCombatTarget() const;
};
