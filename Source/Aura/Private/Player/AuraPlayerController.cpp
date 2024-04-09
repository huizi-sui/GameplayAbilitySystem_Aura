// Liuxijun


#include "Player/AuraPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Interfaction/EnemyInterface.h"

AAuraPlayerController::AAuraPlayerController()
{
	// 多人游戏中的复制本质上是当服务器上的实体发生变化时，
	// 服务器上发生的更改将复制或发送到连接到的所有客户端。
	bReplicates = true;
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CursorTrace();
}
// 光标跟踪将涉及获取光标下的命中结果
void AAuraPlayerController::CursorTrace()
{
	FHitResult CursorHit;
	// 第一个参数是跟踪通道，可以根据可见性通道进行跟踪
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	if(!CursorHit.bBlockingHit)
	{
		return;
	}

	LastActor = ThisActor;
	// 如果转换成功，则是AuraEnemy类型，如果转换失败，返回nullptr
	ThisActor = Cast<IEnemyInterface>(CursorHit.GetActor());

	/**
	 * Line trace from cursor. There are several scenarios:
	 *  A. LastActor is nullptr, and ThisActor is nullptr.
	 *		- Do nothing
	 *  B. LastActor is nullptr, and ThisActor is not nullptr.
	 *		- Highlight ThisActor.
	 *  C. LastActor is not nullptr, and ThisActor is nullptr.
	 *		- UnHighlight LastActor
	 *  D. Both are not nullptr, and LastActor != ThisActor
	 *		- UnHighlight LastActor && Highlight ThisActor
	 *	E. Both are not nullptr, and LastActor == ThisActor
	 *		- Do nothing
	 */
	if(ThisActor == LastActor)
	{
		return;
	}
	if(LastActor != nullptr)
	{
		LastActor->UnHighlightActor();
	}
	if(ThisActor != nullptr)
	{
		ThisActor->HighlightActor();
	}
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// 添加输入映射上下文
	// 断言
	// 该输入映射上下文可能是个有效指针，这需要在蓝图中进行设置。
	// 如果没有，则是个无效指针。会遇到各种问题，例如输入不起效果。
	// 使用断言，停止运行。所以强制在玩家控制器上设置输入映射上下文
	check(AuraContext);

	// 将输入映射上下文绑定到玩家控制器
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(Subsystem);

	Subsystem->AddMappingContext(AuraContext, 0);

	// 设置鼠标可见
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	// 输入模式结构体，使用它的话能够使用键盘和鼠标的输入，还能使用输入来影响UI
	FInputModeGameAndUI InputModeData;
	// 使用设置锁定鼠标来视口行为, 选择不锁定
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	// 获取输入模式数据并在捕获期间使用设置隐藏光标为false
	InputModeData.SetHideCursorDuringCapture(false);

	// 使用此输入模式数据，使用玩家控制器函数设置输入模式传递
	SetInputMode(InputModeData);
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	// 将输入组件转换为增强型输入组件
	// CastChecked, 如果转换失败，则程序崩溃
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	// 希望将移动输入操作绑定到它，采用绑定操作。
	// Move被绑定到MoveAction
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
}

void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
	// 首先获取输入操作值, 我们是在二维上移动的
	// 当我们按下W或S时，InputAxisVector的x将为0，y为1或-1.
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	// 使用添加运动输入来为我们受控的pawn添加向前的运动
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	// 有了方向，可以向受控pawn添加运动输入
	if(APawn* ControlledPawn = GetPawn())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}


