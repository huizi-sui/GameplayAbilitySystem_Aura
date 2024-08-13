// Liuxijun


#include "Checkpoint/MapEntrance.h"

#include "Components/SphereComponent.h"
#include "Game/AuraGameModeBase.h"
#include "Interfaction/PlayerInterface.h"
#include "Kismet/GameplayStatics.h"

AMapEntrance::AMapEntrance(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	Sphere->SetupAttachment(MoveToComponent);
}

void AMapEntrance::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// 保存的Player Tag是另一张地图上的Player Start Tag
	if (OtherActor->Implements<UPlayerInterface>())
	{
		bReached = true;

		if (const AAuraGameModeBase* AuraGameMode = Cast<AAuraGameModeBase>(UGameplayStatics::GetGameMode(this)))
		{
			// Save the World we are traveling to.
			AuraGameMode->SaveWorldState(GetWorld(), DestinationMap.ToSoftObjectPath().GetAssetName());
		}
		IPlayerInterface::Execute_SaveProgress(OtherActor, DestinationPlayerStartTag);

		UGameplayStatics::OpenLevelBySoftObjectPtr(this, DestinationMap);
	}
}

void AMapEntrance::LoadActor_Implementation()
{
	// Do nothing when loading a Map Entrance
}

void AMapEntrance::HighlightActor_Implementation()
{
	CheckpointMesh->SetRenderCustomDepth(true);
}
