// Liuxijun

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "ExecCalc_Damage.generated.h"

/**
 * 可以捕获属性
 * 可以更改多个Attribute
 * 可以拥有程序逻辑
 *
 * 但是没有预测
 * 只能是即时或周期性Gameplay Effect
 * Capturing 不会运行PreAttributeChange()函数，任何在这里Clamping必须再次执行
 * 只会被Gameplay Abilities在Server上执行，当Net Execution Policies是Local Predicted，Server Initiated and Server Only
 */
UCLASS()
class AURA_API UExecCalc_Damage : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()

public:

	UExecCalc_Damage();
	void DetermineDebuff(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	                     const FGameplayEffectSpec& Spec,
	                     const FAggregatorEvaluateParameters& EvaluateParameters,
	                     const TMap<FGameplayTag, FGameplayEffectAttributeCaptureDefinition>& InTagsToDefs) const;

	// 执行这个自定义计算类会发生什么，什么类型的
	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
		FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;

	
};
