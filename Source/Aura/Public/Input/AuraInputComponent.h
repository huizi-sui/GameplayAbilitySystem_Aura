// Liuxijun

#pragma once

#include "CoreMinimal.h"
#include "AuraInputConfig.h"
#include "EnhancedInputComponent.h"
#include "AuraInputComponent.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:
	
	// 从玩家控制器调用该函数，将输入绑定到回调函数，希望这些回调函数成为函数的参数
	template<class UserClass, typename PressedFuncType, typename ReleasedFuncType, typename HoldFuncType>
	void BindAbilityActions(const UAuraInputConfig* InputConfig, UserClass* Object, PressedFuncType PressedFunc,
		ReleasedFuncType ReleasedFunc, HoldFuncType HoldFunc);
};

template <class UserClass, typename PressedFuncType, typename ReleasedFuncType, typename HoldFuncType>
void UAuraInputComponent::BindAbilityActions(const UAuraInputConfig* InputConfig, UserClass* Object,
	PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc, HoldFuncType HoldFunc)
{
	check(InputConfig);

	// 为什么要将相同的函数绑定到所有输入呢？
	// 因为有能力传递游戏标签，因此如果将按下、保持和释放三个相同函数绑定到所有输入操作，
	// 我们可以通过标签识别这些输入，然后将它们传递给能力系统组件，然后决定激活哪些能力。
	for (const FAuraInputAction& Action : InputConfig->AbilityInputActions)
	{
		if (Action.InputAction && Action.InputTag.IsValid())
		{
			if (PressedFunc)
			{
				BindAction(Action.InputAction, ETriggerEvent::Started, Object, PressedFunc, Action.InputTag);
			}
			if (HoldFunc)
			{
				BindAction(Action.InputAction, ETriggerEvent::Triggered, Object, HoldFunc, Action.InputTag);
			}
			if (ReleasedFunc)
			{
				BindAction(Action.InputAction, ETriggerEvent::Completed, Object, ReleasedFunc, Action.InputTag);
			}
		}
	}
}
