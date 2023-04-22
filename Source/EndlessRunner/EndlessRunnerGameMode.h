// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EndlessRunnerGameMode.generated.h"

class AMyPlatform;

UCLASS(minimalapi) class AEndlessRunnerGameMode : public AGameModeBase {
	GENERATED_BODY()

  public:
	AEndlessRunnerGameMode();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float StartingPoint = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MinLength = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float PlatformMoveSpeed = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<TSubclassOf<AMyPlatform>> SpawnablePlatforms;

  private:
	float Length = 0;
	TArray<AMyPlatform *> Platforms;

	void SpawnPlatforms();
	void StorePlatform(AMyPlatform *Platform);

  protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

  public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
