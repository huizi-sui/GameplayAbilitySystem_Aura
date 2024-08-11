// Liuxijun

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "NiagaraComponent.h"
#include "PassiveNiagaraComponent.generated.h"

class UAuraAbilitySystemComponent;
/**
 * 
 */
UCLASS()
class AURA_API UPassiveNiagaraComponent : public UNiagaraComponent
{
	GENERATED_BODY()

public:

	UPassiveNiagaraComponent();

	UPROPERTY(EditDefaultsOnly)
	FGameplayTag PassiveSpellTag;

protected:

	virtual void BeginPlay() override;

	void OnPassiveActive(const FGameplayTag& AbilityTag, bool bActivate);

	void ActivateIfEquipped(UAuraAbilitySystemComponent* AuraASC);
};


