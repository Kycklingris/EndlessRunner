// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EndlessRunnerGameMode.generated.h"

UCLASS(minimalapi) class AEndlessRunnerGameMode : public AGameModeBase {
	GENERATED_BODY()

  public:
	AEndlessRunnerGameMode();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float MaxSpeedModifier = 10.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float ModifierGainPerMinute = 1.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float StartingPoint = -3000.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float MinLength = 20000.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float PlatformMoveSpeed = 200.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float SpaceBetweenPlatforms = 300.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<TSubclassOf<class AMyPlatform>> SpawnablePlatforms;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float FirstObstacleSpawnPoint = 5.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float ObstacleSpawnPoint = 17000.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float DistanceBetweenObstacles = 150.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float ObstacleMinMultiplier = 0.5f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float ObstacleMaxMultiplier = 2.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<TSubclassOf<class AMovingObstacle>> SpawnableObstacles;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float SuccessfulDodgePercent = 20.0f;

	void SuccessfulDodge();
	void RemoveObstacle(class AMovingObstacle *Obstacle);

  private:
	TArray<AMyPlatform *> Platforms;
	AMyPlatform *LastPlatform;

	void SpawnPlatforms();
	void PreSpawnPlatforms();

	TArray<class AMovingObstacle *> ObstaclesLeft;
	TArray<class AMovingObstacle *> ObstaclesRight;

	class AMovingObstacle *LastObstacle;
	int SpawnSide = 1;

	void SpawnObstacle();
	void PreSpawnObstacles();

  protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

  public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};