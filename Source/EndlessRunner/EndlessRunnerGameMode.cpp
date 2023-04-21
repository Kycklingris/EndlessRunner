// Copyright Epic Games, Inc. All Rights Reserved.

#include "EndlessRunnerGameMode.h"
#include "Private/MyPlatform.h"
#include "UObject/ConstructorHelpers.h"

AEndlessRunnerGameMode::AEndlessRunnerGameMode() {

}

// Called when the game starts or when spawned
void AEndlessRunnerGameMode::BeginPlay() {
	Super::BeginPlay();
	SpawnPlatforms();
}

void AEndlessRunnerGameMode::SpawnPlatforms() {
	if (SpawnablePlatforms.Num() == 0) {
		return;
	}

	// Spawn new platforms until atleast minimum length.
	while (true) {
		int Index = FMath::RandRange(0, SpawnablePlatforms.Num() - 1);

		FActorSpawnParameters SpawnInfo;

		auto Platform = GetWorld()->SpawnActor<AMyPlatform>(
			SpawnablePlatforms[Index], FVector(0.f, 0.f, 0.f), FRotator(0.f), SpawnInfo);

		float PlatformLength = Platform->GetLength();
		Platform->SetActorLocation(FVector((PlatformLength / 2.f) + StartingPoint + Length, 0.f, 0.f));
		Length += PlatformLength;

		if (Length >= MinLength) {
			break;
		}
	}
}

float AEndlessRunnerGameMode::UpdateLength(float Modifier) {
	Length += Modifier;

	if (Length < MinLength) {
		SpawnPlatforms();
	}

	return Length;
}

float AEndlessRunnerGameMode::GetLength() {
	return Length;
}