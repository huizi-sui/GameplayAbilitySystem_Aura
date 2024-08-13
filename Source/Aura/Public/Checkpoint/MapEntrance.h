// Liuxijun

#pragma once

#include "CoreMinimal.h"
#include "Checkpoint/Checkpoint.h"
#include "MapEntrance.generated.h"

// 地图切换

/**
 * 
 */
UCLASS()
class AURA_API AMapEntrance : public ACheckpoint
{
	GENERATED_BODY()

protected:

	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

public:

	AMapEntrance(const FObjectInitializer& ObjectInitializer);

	/* Highlight Interface */
	virtual void HighlightActor_Implementation() override;
	/* End Highlight Interface */

	/* Save Interface */
    virtual void LoadActor_Implementation() override;
    /* End Save Interface */

	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<UWorld> DestinationMap;

	// 在特定的Player Start处生成
	UPROPERTY(EditAnywhere)
	FName DestinationPlayerStartTag;
};
