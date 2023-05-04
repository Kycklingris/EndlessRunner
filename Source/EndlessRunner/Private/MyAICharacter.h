// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyCharacter.h"
#include "MyAICharacter.generated.h"

/**
 *
 */
UCLASS()
class AMyAICharacter : public AMyCharacter {
	GENERATED_BODY()

  public:
	// Sets default values for this character's properties
	AMyAICharacter();

  protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

  public:
	virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;

	UPROPERTY(EditDefaultsOnly)
	class UBoxComponent *AICollider = nullptr;

  private:
	UFUNCTION()
	void OnAIObstacleBeginOverlap(UPrimitiveComponent *OverlappedComp, AActor *OtherActor,
		UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

	float LastOverlapEvent = 0.f;
	float TimeBetweenOverlaps = 0.5f;
};
