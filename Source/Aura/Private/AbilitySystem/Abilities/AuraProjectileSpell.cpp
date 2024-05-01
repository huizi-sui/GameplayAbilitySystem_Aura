// Liuxijun


#include "AbilitySystem/Abilities/AuraProjectileSpell.h"

#include "Actor/AuraProjectile.h"
#include "Interfaction/CombatInterface.h"

void UAuraProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                           const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                           const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	// 在Server上生成，而不是本地, 所以设置Actor的bReplicates为true
	// 这个射弹成为一个复制的Actor，Server生成并移动它，处理它的位置等，Client只会看到复制版本
	const bool bIsServer = HasAuthority(&ActivationInfo);
	if (!bIsServer)
	{
		return;
	}
	// 生成一个射弹Actor, 为Actor设置游戏效果或者游戏效果规范。
	ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo());
	if (CombatInterface)
	{
		const FVector SocketLocation = CombatInterface->GetCombatSocketLocation();
		FTransform SpawnTransform;
		SpawnTransform.SetLocation(SocketLocation);
		// TODO: Set the Projectile Rotation
		AAuraProjectile* Projectile = GetWorld()->SpawnActorDeferred<AAuraProjectile>(
			ProjectileClass,
			SpawnTransform,
			GetOwningActorFromActorInfo(),
			Cast<APawn>(GetOwningActorFromActorInfo()),
			// 希望它始终生成，无论碰撞或重叠如何。
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
		// 分两步完成，可以设置一些东西
		// TODO: Give the Projectile a Gameplay Effect Spec for causing Damage.
		Projectile->FinishSpawning(SpawnTransform);
	}
}
