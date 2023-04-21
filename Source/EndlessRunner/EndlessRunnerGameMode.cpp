// Copyright Epic Games, Inc. All Rights Reserved.

#include "EndlessRunnerGameMode.h"
#include "Private/MyPlatform.h"
#include "UObject/ConstructorHelpers.h"

AEndlessRunnerGameMode::AEndlessRunnerGameMode() {
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AEndlessRunnerGameMode::BeginPlay() {
	Super::BeginPlay();
	SpawnPlatforms();
}

void AEndlessRunnerGameMode::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	if (Length < MinLength) {
		SpawnPlatforms();
	}

	for (AMyPlatform *Platform : Platforms) {
		if (!IsValid(Platform) || Platform->IsActorBeingDestroyed()) {
			continue;
		}

		auto PlatformLength = Platform->GetLength();
		auto Location = Platform->GetActorLocation();
		auto NewLocation = FVector(Location.X - PlatformMoveSpeed * DeltaTime, 0.f, 0.f);
		Platform->SetActorLocation(NewLocation);

		if (NewLocation.X + PlatformLength / 2.f < StartingPoint) {
			Length = Length - PlatformLength;
			Platform->Destroy();
		}
	}
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
		StorePlatform(Platform);

		if (Length >= MinLength) {
			return;
		}
	}
}

void AEndlessRunnerGameMode::StorePlatform(AMyPlatform *Platform) {
	for (int i = 0; i < Platforms.Num(); i++) {
		if (!IsValid(Platforms[i])) {
			Platforms[i] = Platform;
			return;
		}
	}

	Platforms.Add(Platform);
}