// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "MySaveGame.generated.h"

/**
 *
 */
UCLASS()
class UMySaveGame : public USaveGame {
	GENERATED_BODY()
  public:
	TArray<int> Highscores;
};
