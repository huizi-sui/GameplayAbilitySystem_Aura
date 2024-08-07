// Liuxijun


#include "AbilitySystem/AbilityTasks/TargetDataUnderMouse.h"

#include "AbilitySystemComponent.h"
#include "Aura/Aura.h"

UTargetDataUnderMouse* UTargetDataUnderMouse::CreateTargetDataUnderMouse(UGameplayAbility* OwningAbility)
{
	UTargetDataUnderMouse* MyObj = NewAbilityTask<UTargetDataUnderMouse>(OwningAbility);
	return MyObj;
}

void UTargetDataUnderMouse::Activate()
{
	// Is Local Controlled
	if (Ability->GetCurrentActorInfo()->IsLocallyControlled())
	{
		SendMouseCursorData();
	}
	else
	{
		const FGameplayAbilitySpecHandle SpecHandle = GetAbilitySpecHandle();
		const FPredictionKey PredictionKey = GetActivationPredictionKey();
		// 向代表绑定委托，以便代表接收到Target Data后，向该委托广播Target Data
		AbilitySystemComponent.Get()->AbilityTargetDataSetDelegate(SpecHandle, PredictionKey).AddUObject(this,
			&UTargetDataUnderMouse::OnTargetDataReplicatedCallback);
		// 如果服务器先调用Activate函数，绑定委托，然后Target Data通过RPC复制的时间，则委托会被广播，无需处理
		// 如果服务器调用Activate函数时，Target Data已经到达服务器，所以绑定委托前，广播已经发生了，此时需要调用CallReplicatedTargetDataDelegatesIfSet()函数，
		// 再次强制广播数据，使得各个委托处理Target Data
		const bool bCalledDelegate = AbilitySystemComponent.Get()->CallReplicatedTargetDataDelegatesIfSet(SpecHandle, PredictionKey);
		if (!bCalledDelegate)
		{
			SetWaitingOnRemotePlayerData();
		}
	}
}

void UTargetDataUnderMouse::SendMouseCursorData() const
{
	// 这个范围内的一切都应该被预测
	FScopedPredictionWindow ScopedPredictionWindow(AbilitySystemComponent.Get());
	
	APlayerController* PC = Ability->GetCurrentActorInfo()->PlayerController.Get();
	FHitResult CursorHit;
	PC->GetHitResultUnderCursor(ECC_Target, false, CursorHit);

	FGameplayAbilityTargetDataHandle DataHandle;
	FGameplayAbilityTargetData_SingleTargetHit* Data = new FGameplayAbilityTargetData_SingleTargetHit();
	Data->HitResult = CursorHit;
	DataHandle.Add(Data);

	// 将数据发送给Server，若Server接收到数据，则会使用代表获取Target Data并进行广播
	AbilitySystemComponent->ServerSetReplicatedTargetData(
		GetAbilitySpecHandle(), // Ability Task由Gameplay Ability调用，所以它能够获得Gameplay Ability Spec
		GetActivationPredictionKey(), // 原先的预测钥匙是与能力的启动相关的。
		DataHandle,
		FGameplayTag(), // 使用一个临时的游戏标签
		AbilitySystemComponent->ScopedPredictionKey);

	// 还应该在本地广播有效数据，以便我们可以看到该光标
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		ValidData.Broadcast(DataHandle);
	}
}

void UTargetDataUnderMouse::OnTargetDataReplicatedCallback(const FGameplayAbilityTargetDataHandle& DataHandle, FGameplayTag ActivationTag)
{
	// 确保能力系统组件知道数据已经被接收，因为当复制的目标数据被接收时，服务器将其存储在特定的数据结构中。
	// 可以告诉能力系统组件我们收到了数据，不需要存储它，也不需要在缓存它。
	AbilitySystemComponent->ConsumeClientReplicatedTargetData(GetAbilitySpecHandle(), GetActivationPredictionKey());
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		ValidData.Broadcast(DataHandle);
	}
}
