// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "EndlessRunnerGameState.generated.h"

/**
 *
 */
UCLASS()
class AEndlessRunnerGameState : public AGameStateBase {
	GENERATED_BODY()

  public:
	float SpeedModifier = 1.0f;

	float Points = 0.f;
};
