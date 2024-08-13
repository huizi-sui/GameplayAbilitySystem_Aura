// Liuxijun

#pragma once

#include "CoreMinimal.h"
#include "Aura/Aura.h"
#include "GameFramework/PlayerStart.h"
#include "Interfaction/HighlightInterface.h"
#include "Interfaction/SaveInterface.h"
#include "Checkpoint.generated.h"

class USphereComponent;
/**
 * 
 */
UCLASS()
class AURA_API ACheckpoint : public APlayerStart, public ISaveInterface, public IHighlightInterface
{
	GENERATED_BODY()

public:

	ACheckpoint(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(BlueprintReadWrite, SaveGame)
	bool bReached = false;

	UPROPERTY(EditDefaultsOnly)
	bool bBindOverlapCallback = true;

	/* Save Interface */
	virtual bool ShouldLoadTransform_Implementation() override { return false; };
	virtual void LoadActor_Implementation() override;
	/* End Save Interface */

	
protected:
	
	UFUNCTION()
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	virtual void BeginPlay() override;

	/* Highlight Interface */
	virtual void HighlightActor_Implementation() override;
	virtual void UnHighlightActor_Implementation() override;
	virtual void SetMoveToLocation_Implementation(FVector& OutDestination) override;
	/* End Highlight Interface */

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> MoveToComponent;

	UPROPERTY(EditDefaultsOnly)
	int32 CustomDepthStencilOverride = CUSTOM_DEPTH_TAN;
	
	UFUNCTION(BlueprintImplementableEvent)
	void CheckpointReached(UMaterialInstanceDynamic* DynamicMaterialInstance);

	UFUNCTION(BlueprintCallable)
	void HandleGlowEffects();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UStaticMeshComponent> CheckpointMesh;
	
	// 重叠体积，用于检查发生重叠事件
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> Sphere;
};
