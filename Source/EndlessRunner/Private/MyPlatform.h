// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyPlatform.generated.h"

class AEndlessRunnerGameMode;
class AEndlessRunnerGameState;

UCLASS()
class AMyPlatform : public AActor
{
	GENERATED_BODY()
	
  public:	
	// Sets default values for this actor's properties
	AMyPlatform();

	float GetLength();

  protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

  private:
	float Length = -1.f;
	AEndlessRunnerGameMode *GameMode;
	AEndlessRunnerGameState *GameState;
};
