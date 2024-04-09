// Liuxijun


#include "Character/AuraCharacter.h"

#include "AbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/AuraPlayerState.h"

AAuraCharacter::AAuraCharacter()
{
	// 首先获得角色运动组件
	GetCharacterMovement()->bOrientRotationToMovement = true;
	// 现在可以通过获取角色移动旋转速率来控制旋转速率。
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);
	// 将运动限制在一个平面上
	GetCharacterMovement()->bConstrainToPlane = true;
	// 确保我们的角色在开始时被捕捉到平面
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// 角色本身不应该使用控制器的旋转
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	
}

void AAuraCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// Init ability actor info for the Server
	InitAbilityActorInfo();
}

void AAuraCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	
	// Init ability actor info for the Client
	InitAbilityActorInfo();
}

void AAuraCharacter::InitAbilityActorInfo()
{
	AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
	check(AuraPlayerState);
	AuraPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(AuraPlayerState, this);
	AbilitySystemComponent = AuraPlayerState->GetAbilitySystemComponent();
	AttributeSet = AuraPlayerState->GetAttributeSet();
}
