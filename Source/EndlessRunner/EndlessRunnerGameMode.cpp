// Copyright Epic Games, Inc. All Rights Reserved.

#include "EndlessRunnerGameMode.h"
#include "Private/MyPlatform.h"
#include "Private/MovingObstacle.h"
#include "UObject/ConstructorHelpers.h"

AEndlessRunnerGameMode::AEndlessRunnerGameMode() {
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AEndlessRunnerGameMode::BeginPlay() {
	Super::BeginPlay();
	SpawnPlatforms();
	PreSpawnObstacles();
}

void AEndlessRunnerGameMode::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	// #fold Spawn Platforms
	if (PlatformsLength < MinLength) {
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
			PlatformsLength -= PlatformLength;
			Platform->Destroy();
		}
	}
	// #endfold

	// Spawn new Obstacle
	if ((LastObstacle->GetActorLocation().X + (LastObstacle->GetLength() / 2.f)) <
		ObstacleSpawnPoint - DistanceBetweenObstacles) {
		SpawnObstacle();
	}

	// GetGameState<>()
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
		Platform->SetActorLocation(FVector((PlatformLength / 2.f) + StartingPoint + PlatformsLength, 0.f, 0.f));
		PlatformsLength += PlatformLength;
		StorePlatform(Platform);

		if (PlatformsLength >= MinLength) {
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

void AEndlessRunnerGameMode::SpawnObstacle() {
	int Index = FMath::RandRange(0, SpawnableObstacles.Num() - 1);

	FActorSpawnParameters SpawnInfo;

	auto Obstacle = GetWorld()->SpawnActor<AMovingObstacle>(
		SpawnableObstacles[Index], FVector(0.f, 0.f, 0.f), FRotator(0.f), SpawnInfo);

	float LengthModifier = FMath::RandRange(1.f, 10.f);
	Obstacle->SetActorRelativeScale3D(FVector(LengthModifier, 1.f, 1.f));
	float ObstacleLength = Obstacle->GetLength();

	Obstacle->MovementSpeed = PlatformMoveSpeed;
	// Obstacle->MovementSpeedMultipier = 1.0f;
	Obstacle->DespawnPoint = StartingPoint;

	float Y = 50.f * SpawnSide;
	SpawnSide *= -1;

	Obstacle->SetActorLocation(FVector((ObstacleLength / 2.f) + ObstacleSpawnPoint, Y, 50.f));

	LastObstacle = Obstacle;
}

void AEndlessRunnerGameMode::PreSpawnObstacles() {
	float CurrentSpawnPoint = FirstObstacleSpawnPoint;

	while (true) {
		int Index = FMath::RandRange(0, SpawnableObstacles.Num() - 1);

		FActorSpawnParameters SpawnInfo;

		auto Obstacle = GetWorld()->SpawnActor<AMovingObstacle>(
			SpawnableObstacles[Index], FVector(0.f, 0.f, 0.f), FRotator(0.f), SpawnInfo);

		float LengthModifier = FMath::RandRange(1.f, 10.f);
		Obstacle->SetActorRelativeScale3D(FVector(LengthModifier, 1.f, 1.f));
		float ObstacleLength = Obstacle->GetLength();

		Obstacle->MovementSpeed = PlatformMoveSpeed;
		// Obstacle->MovementSpeedMultipier = 1.0f;
		Obstacle->DespawnPoint = StartingPoint;

		float Y = 50.f * SpawnSide;

		Obstacle->SetActorLocation(FVector((ObstacleLength / 2.f) + CurrentSpawnPoint, Y, 50.f));

		CurrentSpawnPoint += ObstacleLength + DistanceBetweenObstacles;

		SpawnSide *= -1;

		if (CurrentSpawnPoint >= ObstacleSpawnPoint) {
			LastObstacle = Obstacle;
			return;
		}
	}
}