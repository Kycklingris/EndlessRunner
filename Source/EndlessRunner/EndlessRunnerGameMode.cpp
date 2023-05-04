// Copyright Epic Games, Inc. All Rights Reserved.

#include "EndlessRunnerGameMode.h"
#include "Private/MyPlatform.h"
#include "Private/MovingObstacle.h"
#include "Private/EndlessRunnerGameState.h"
#include "UObject/ConstructorHelpers.h"
#include "MySaveGame.h"
#include "Kismet/GameplayStatics.h"

AEndlessRunnerGameMode::AEndlessRunnerGameMode() {
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AEndlessRunnerGameMode::BeginPlay() {
	Super::BeginPlay();
	PreSpawnPlatforms();
	SpawnPlatforms();
	PreSpawnObstacles();
}

void AEndlessRunnerGameMode::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	auto AGameState = GetGameState<AEndlessRunnerGameState>();

	// #fold Spawn Platforms
	if (LastPlatform->GetActorLocation().X < (StartingPoint + MinLength)) {
		SpawnPlatforms();
	}

	for (AMyPlatform *Platform : Platforms) {
		if (!IsValid(Platform) || Platform->IsActorBeingDestroyed()) {
			continue;
		}

		auto Location = Platform->GetActorLocation();
		Location.X -= PlatformMoveSpeed * AGameState->SpeedModifier * DeltaTime;
		Platform->SetActorLocation(Location);

		if (Location.X < StartingPoint) {
			Platforms.Remove(Platform);
			Platform->Destroy();
		}
	}
	// #endfold

	// Spawn new Obstacle
	if ((LastObstacle->GetActorLocation().X + (LastObstacle->GetLength() / 2.f)) <
		ObstacleSpawnPoint - DistanceBetweenObstacles) {
		SpawnObstacle();
	}

	AGameState->SpeedModifier += ModifierGainPerMinute * DeltaTime / 60.f;
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
		auto Platform2 = GetWorld()->SpawnActor<AMyPlatform>(
			SpawnablePlatforms[Index], FVector(0.f, 0.f, 0.f), FRotator(0.f), SpawnInfo);

		float PlatformLength = Platform->GetLength();

		auto Location = LastPlatform->GetActorLocation();
		auto LastLength = LastPlatform->GetLength();

		float X = Location.X + (LastLength / 2.f) + (PlatformLength / 2.f);
		Platform->SetActorLocation(FVector(X, -(SpaceBetweenPlatforms / 2.f), 0.f));
		Platform2->SetActorLocation(FVector(X, (SpaceBetweenPlatforms / 2.f), 0.f));

		Platforms.Add(Platform);
		Platforms.Add(Platform2);

		LastPlatform = Platform;
		if (Location.X >= MinLength) {
			return;
		}
	}
}

void AEndlessRunnerGameMode::PreSpawnPlatforms() {
	if (SpawnablePlatforms.Num() == 0) {
		return;
	}
	auto PlatformsLength = 0.f;

	// Spawn new platforms until atleast minimum length.
	while (true) {
		int Index = FMath::RandRange(0, SpawnablePlatforms.Num() - 1);

		FActorSpawnParameters SpawnInfo;

		auto Platform = GetWorld()->SpawnActor<AMyPlatform>(
			SpawnablePlatforms[Index], FVector(0.f, 0.f, 0.f), FRotator(0.f), SpawnInfo);
		auto Platform2 = GetWorld()->SpawnActor<AMyPlatform>(
			SpawnablePlatforms[Index], FVector(0.f, 0.f, 0.f), FRotator(0.f), SpawnInfo);

		float PlatformLength = Platform->GetLength();
		Platform->SetActorLocation(
			FVector((PlatformLength / 2.f) + StartingPoint + PlatformsLength, -(SpaceBetweenPlatforms / 2.f), 0.f));
		Platform2->SetActorLocation(
			FVector((PlatformLength / 2.f) + StartingPoint + PlatformsLength, (SpaceBetweenPlatforms / 2.f), 0.f));

		PlatformsLength += PlatformLength;

		Platforms.Add(Platform);
		Platforms.Add(Platform2);

		LastPlatform = Platform;
		if (PlatformsLength >= MinLength) {
			return;
		}
	}
}

void AEndlessRunnerGameMode::SpawnObstacle() {
	if (SpawnableObstacles.Num() == 0) {
		return;
	}
	int Index = FMath::RandRange(0, SpawnableObstacles.Num() - 1);

	FActorSpawnParameters SpawnInfo;

	auto Obstacle = GetWorld()->SpawnActor<AMovingObstacle>(
		SpawnableObstacles[Index], FVector(0.f, 0.f, 0.f), FRotator(0.f), SpawnInfo);
	auto Obstacle2 = GetWorld()->SpawnActor<AMovingObstacle>(
		SpawnableObstacles[Index], FVector(0.f, 0.f, 0.f), FRotator(0.f), SpawnInfo);

	float LengthModifier = FMath::RandRange(1.f, 10.f);
	Obstacle->SetActorRelativeScale3D(FVector(LengthModifier, 1.f, 1.f));
	Obstacle2->SetActorRelativeScale3D(FVector(LengthModifier, 1.f, 1.f));

	float ObstacleLength = Obstacle->GetLength();

	Obstacle->MovementSpeed = PlatformMoveSpeed;
	Obstacle->DespawnPoint = StartingPoint;
	Obstacle2->MovementSpeed = PlatformMoveSpeed;
	Obstacle2->DespawnPoint = StartingPoint;

	float Y = 50.f * SpawnSide;
	SpawnSide *= -1;

	Obstacle->SetActorLocation(
		FVector((ObstacleLength / 2.f) + ObstacleSpawnPoint, -(SpaceBetweenPlatforms / 2.f) + Y, 50.f));
	Obstacle2->SetActorLocation(
		FVector((ObstacleLength / 2.f) + ObstacleSpawnPoint, (SpaceBetweenPlatforms / 2.f) + Y, 50.f));

	LastObstacle = Obstacle;
}

void AEndlessRunnerGameMode::PreSpawnObstacles() {
	if (SpawnableObstacles.Num() == 0) {
		return;
	}
	float CurrentSpawnPoint = FirstObstacleSpawnPoint;

	while (true) {
		int Index = FMath::RandRange(0, SpawnableObstacles.Num() - 1);

		FActorSpawnParameters SpawnInfo;

		auto Obstacle = GetWorld()->SpawnActor<AMovingObstacle>(
			SpawnableObstacles[Index], FVector(0.f, 0.f, 0.f), FRotator(0.f), SpawnInfo);
		auto Obstacle2 = GetWorld()->SpawnActor<AMovingObstacle>(
			SpawnableObstacles[Index], FVector(0.f, 0.f, 0.f), FRotator(0.f), SpawnInfo);

		float LengthModifier = FMath::RandRange(1.f, 10.f);
		Obstacle->SetActorRelativeScale3D(FVector(LengthModifier, 1.f, 1.f));
		Obstacle2->SetActorRelativeScale3D(FVector(LengthModifier, 1.f, 1.f));

		float ObstacleLength = Obstacle->GetLength();

		Obstacle->MovementSpeed = PlatformMoveSpeed;
		Obstacle->DespawnPoint = StartingPoint;
		Obstacle2->MovementSpeed = PlatformMoveSpeed;
		Obstacle2->DespawnPoint = StartingPoint;

		float Y = 50.f * SpawnSide;

		Obstacle->SetActorLocation(
			FVector((ObstacleLength / 2.f) + CurrentSpawnPoint, -(SpaceBetweenPlatforms / 2.f) + Y, 50.f));
		Obstacle2->SetActorLocation(
			FVector((ObstacleLength / 2.f) + CurrentSpawnPoint, (SpaceBetweenPlatforms / 2.f) + Y, 50.f));

		CurrentSpawnPoint += ObstacleLength + DistanceBetweenObstacles;

		SpawnSide *= -1;

		if (CurrentSpawnPoint >= ObstacleSpawnPoint) {
			LastObstacle = Obstacle;
			return;
		}
	}
}