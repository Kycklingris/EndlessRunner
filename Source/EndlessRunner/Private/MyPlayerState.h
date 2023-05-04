// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "MyPlayerState.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class AMyPlayerState : public APlayerState
{
	GENERATED_BODY()

  public:
	UPROPERTY(BlueprintReadOnly)
	float Points = 0.f;

	UPROPERTY(BlueprintReadOnly)
	int Health = 3;
};
