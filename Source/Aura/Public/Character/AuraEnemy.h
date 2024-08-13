// Liuxijun

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "Interfaction/EnemyInterface.h"
#include "AbilitySystem/Data/CharacterClassInfo.h"
#include "Interfaction/HighlightInterface.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "AuraEnemy.generated.h"


class AAuraAIController;
class UBehaviorTree;
class UWidgetComponent;
/**
 * 
 */
UCLASS()
class AURA_API AAuraEnemy : public AAuraCharacterBase, public IEnemyInterface, public IHighlightInterface
{
	GENERATED_BODY()

public:
	AAuraEnemy();

	virtual void PossessedBy(AController* NewController) override;

	/** Highlight Interface */
	virtual void HighlightActor_Implementation() override;
	virtual void UnHighlightActor_Implementation() override;
	virtual void SetMoveToLocation_Implementation(FVector& OutDestination) override;
	/** End Highlight Interface */

	/** Combat Interface */
	virtual int32 GetPlayerLevel_Implementation() const override;
	/** End Combat Interface */

	virtual void Die(const FVector& DeathImpulse) override;
	
	void HitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount);

	virtual void SetCombatTarget_Implementation(AActor* InCombatTarget) override;

	virtual AActor* GetCombatTarget_Implementation() const override;

	// 创建一个委托，从敌人本身向我们的小部件广播
	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnMaxHealthChanged;

	// 将其暴露给蓝图
	UPROPERTY(BlueprintReadOnly, Category = "Combat")
	bool bHitReacting = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat")
    float LifeSpan = 5.f;

	UPROPERTY(BlueprintReadOnly, Category = "Combat")
	TObjectPtr<AActor> CombatTarget;

protected:
	virtual void BeginPlay() override;

	virtual void InitAbilityActorInfo() override;
	virtual void InitializeDefaultAttribute() const override;

	virtual void StunTagChanged(const FGameplayTag CallbackTag, int32 NewCount) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults")
	int32 Level = 1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UWidgetComponent> HealthBar;

	UPROPERTY(EditAnywhere, Category = "AI")
	TObjectPtr<UBehaviorTree> BehaviorTree;

	UPROPERTY()
	TObjectPtr<AAuraAIController> AuraAIController;
};
