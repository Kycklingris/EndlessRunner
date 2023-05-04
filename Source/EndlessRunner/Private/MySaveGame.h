// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Containers/UnrealString.h"
#include "MySaveGame.generated.h"

/**
 *
 */
UCLASS()
class UMySaveGame : public USaveGame {
	GENERATED_BODY()
  private:
	static inline FString SaveSlotName = FString("Main");

  public:
	UPROPERTY()
	TArray<int> Highscores;

  public:
	UFUNCTION(BlueprintCallable)
	static UMySaveGame *LoadSave();
	UFUNCTION(BlueprintCallable)
	static void SaveScore(int Score);
};
