// Liuxijun


#include "AbilitySystem/ModMagCalc/MMC_MaxHealth.h"

#include "AbilitySystem/AuraAttributeSet.h"
#include "Interfaction/CombatInterface.h"

UMMC_MaxHealth::UMMC_MaxHealth()
{
	// 指定要捕获的属性，且可以访问属性或属性集
	VigorDef.AttributeToCapture = UAuraAttributeSet::GetVigorAttribute();
	// 捕获的是游戏效果的施加者还是目标者的
	VigorDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	// 当捕获对象是Source时
	// 若为true，则当Gameplay Effect Spec被创建时捕获该Attribute Value
	// 若为false，则当Gameplay Effect Applied时捕获该Attribute Value
	// 当捕获对象是Target时，只在Effect Application时捕获
	VigorDef.bSnapshot = false;

	// 将其添加到要捕获的属性列表中
	RelevantAttributesToCapture.Add(VigorDef);
}

float UMMC_MaxHealth::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	// Get tags from source and target
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = SourceTags;
	EvaluateParameters.TargetTags = TargetTags;

	// 将这些参数传递给特定函数才能捕获属性
	float Vigor = 0.f;
	GetCapturedAttributeMagnitude(VigorDef, Spec, EvaluateParameters, Vigor);
	Vigor = FMath::Max<float>(Vigor, 0.f);

	int32 PlayerLevel = 1;
	if (Spec.GetContext().GetSourceObject()->Implements<UCombatInterface>())
	{
		PlayerLevel = ICombatInterface::Execute_GetPlayerLevel(Spec.GetContext().GetSourceObject());
	} 

	return 80.f + 2.5f * Vigor + 10.f * PlayerLevel;
}
