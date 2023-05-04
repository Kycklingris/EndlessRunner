// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyCharacter.generated.h"

UCLASS()
class AMyCharacter : public APawn {
	GENERATED_BODY()

  public:
	// Sets default values for this character's properties
	AMyCharacter();

  protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

  public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent *PlayerInputComponent) override;

  public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class USkeletalMeshComponent *Mesh;

	UPROPERTY(EditDefaultsOnly)
	float CameraDistance = 250.f;

	int Position = -1;

	UPROPERTY(EditDefaultsOnly)
	class UInputAction *LeftAction;

	UPROPERTY(EditDefaultsOnly)
	class UInputAction *RightAction;

	UPROPERTY(EditDefaultsOnly)
	class UInputMappingContext *MappingContext;

	void Input_Move_Left(const struct FInputActionValue &InputActionValue);

	void Input_Move_Right(const struct FInputActionValue &InputActionValue);

	UPROPERTY(EditDefaultsOnly)
	float TimeBetweenHits = 1.5f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float PointsPerMinute = 1000;

	void UpdateHealth(int Modifier);

	UFUNCTION()
	void OnObstacleBeginOverlap(UPrimitiveComponent *OverlappedComp, AActor *OtherActor, UPrimitiveComponent *OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

	UFUNCTION()
	void OnObstacleHit(UPrimitiveComponent *HitComp, AActor *OtherActor, UPrimitiveComponent *OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

  private:
	class UCameraComponent *OurCamera;
	float LastHit = -500.f;
};