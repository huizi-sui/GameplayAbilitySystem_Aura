// Liuxijun


#include "Actor/MagicCircle.h"

#include "Components/DecalComponent.h"

AMagicCircle::AMagicCircle()
{
	PrimaryActorTick.bCanEverTick = false;

	MagicCircleDecal = CreateDefaultSubobject<UDecalComponent>(FName("MagicCircleDecal"));
	MagicCircleDecal->SetupAttachment(GetRootComponent());
}

void AMagicCircle::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AMagicCircle::BeginPlay()
{
	Super::BeginPlay();
	
}
