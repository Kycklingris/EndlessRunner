// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Containers/UnrealString.h"
#include "MySaveGame.generated.h"

/**
 *
 */
UCLASS(BlueprintType)
class UMySaveGame : public USaveGame {
	GENERATED_BODY()
  private:
	static inline FString SaveSlotName = FString("Main");

  public:
	UPROPERTY(BlueprintReadOnly)
	TArray<int> Highscores;

  public:
	UFUNCTION(BlueprintCallable)
	static UMySaveGame *LoadSave();
	UFUNCTION(BlueprintCallable)
	static void SaveScore(int Score);
};
