// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingObstacle.generated.h"

UCLASS()
class AMovingObstacle : public AActor {
	GENERATED_BODY()

  public:
	// Sets default values for this actor's properties
	AMovingObstacle();

  protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

  public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	USceneComponent *DefaultRoot;

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	float GetLength();

	float MovementSpeed = 0.0f;
	float MovementSpeedMultipier = 1.0f;

	float DespawnPoint = 0.f;

	UPROPERTY(EditDefaultsOnly)
	class UStaticMeshComponent *Cube;

  private:
	float Length = -1.f;
};
