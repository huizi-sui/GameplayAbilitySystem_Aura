// Liuxijun


#include "AbilitySystem/Abilities/AuraSummonAbility.h"

#include "Kismet/KismetSystemLibrary.h"

TArray<FVector> UAuraSummonAbility::GetSpawnLocations()
{
	// 1. 获取Actor的前向向量
	const FVector Forward = GetAvatarActorFromActorInfo()->GetActorForwardVector();
	const FVector Location = GetAvatarActorFromActorInfo()->GetActorLocation();
	const float DeltaSpread = SpawnSpread / NumMinions;

	const FVector LeftOfSpread = Forward.RotateAngleAxis(-SpawnSpread * 0.5f, FVector::UpVector);
	TArray<FVector> SpawnLocations;
	for (int32 i = 0; i < NumMinions; i++)
	{
		const FVector Direction = LeftOfSpread.RotateAngleAxis(DeltaSpread * i, FVector::UpVector);
		const FVector ChosenSpawnLocation = Location + Direction * FMath::RandRange(MinSpawnDistance, MaxSpawnDistance);
		SpawnLocations.Add(ChosenSpawnLocation);
		
		UKismetSystemLibrary::DrawDebugArrow(GetAvatarActorFromActorInfo(), Location,
	Location + Direction * MaxSpawnDistance, 4.f, FLinearColor::Green, 3.f);

		DrawDebugSphere(GetWorld(), ChosenSpawnLocation, 15.f, 12, FColor::Blue, false, 3.f);
	}

	return SpawnLocations;
}
