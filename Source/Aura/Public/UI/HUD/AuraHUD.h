// Liuxijun

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "UI/WidgetController/SpellMenuWidgetController.h"
#include "AuraHUD.generated.h"

class UAttributeMenuWidgetController;
class UAttributeSet;
class UAbilitySystemComponent;
struct FWidgetControllerParams;
class UOverlayWidgetController;
class UAuraUserWidget;

/**
 *  HUD是显示屏幕上覆盖的元素的基本对象。每个本地玩家都有自己的AHUD类实例，这个实例会绘制到个人视口上。
 *
 *  创建相关Widget，将其添加到视口上。所以自定义HUD
 *  Overlay是最顶层的Widget，所有其他Widget都在它上面，所以HUD需要创建它，也就需要知道它的类型是什么(TSubClassOf)
 *
 *  另外，每个Player Controller都知道它们的HUD，即HUD始终可以通过Player Controller访问到。
 *  在服务器端，当Player Controller Possess Pawn时，此时Pawn， Player Controller都是有效的，
 *  Player State也存在于Player Controller中，所以Player State中的ASC和AS也是有效的，然后调用函数AAuraCharacter::InitAbilityInfo
 *  在客户端，在函数OnRep_PlayerState中，服务器将Player State复制到客户端(当服务器上Player Controller Possess Pawn后，会将Pawn的Player
 *  State指针指向Player Controller中的Player State)，所以此时上述四个也都是有效的，调用函数AAuraCharacter::InitAbilityInfo
 *
 *  在InitAbilityInfo中，需要注意只有每个本地玩家才具有HUD，所以需要检查HUD是否为nullptr，如果不是，则初始化Widget Controller。
 */
UCLASS()
class AURA_API AAuraHUD : public AHUD
{
	GENERATED_BODY()

public:
	
	UOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& WidgetControllerParams);

	UAttributeMenuWidgetController* GetAttributeMenuWidgetController(const FWidgetControllerParams& WidgetControllerParams);

	USpellMenuWidgetController* GetSpellMenuWidgetController(const FWidgetControllerParams& SpellMenuControllerParams);

	void InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);

protected:
	
private:

	UPROPERTY()
	TObjectPtr<UAuraUserWidget> OverlayWidget;

	// 要创建小部件，需要知道要创建的小部件的类
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> OverlayWidgetClass;
	
	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UAttributeMenuWidgetController> AttributeMenuWidgetClass;

	UPROPERTY()
	TObjectPtr<UAttributeMenuWidgetController> AttributeMenuWidgetController;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;

	UPROPERTY()
	TObjectPtr<USpellMenuWidgetController> SpellMenuWidgetController;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<USpellMenuWidgetController> SpellMenuWidgetControllerClass;
};
