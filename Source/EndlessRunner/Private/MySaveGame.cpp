// Fill out your copyright notice in the Description page of Project Settings.

#include "MySaveGame.h"
#include "Kismet/GameplayStatics.h"

void UMySaveGame::SaveScore(int Score) {
	UMySaveGame *OldSave = Cast<UMySaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, 0));
	UMySaveGame *NewSave = Cast<UMySaveGame>(UGameplayStatics::CreateSaveGameObject(UMySaveGame::StaticClass()));

	TArray<int> OldHighscores;
	if (OldSave != nullptr) {
		OldHighscores = OldSave->Highscores;
	}

	if (OldHighscores.Num() == 0) {
		NewSave->Highscores.Add(Score);
	} else {
		bool FoundPlace = false;
		// Make sure that at most 50 highscores are saved.
		for (int i = 0; i < OldHighscores.Num(); i++) {
			if (!FoundPlace && Score > OldHighscores[i]) {
				FoundPlace = true;
				NewSave->Highscores.Add(Score);
				i--;
			} else {
				NewSave->Highscores.Add(OldHighscores[i]);
			}

			if (NewSave->Highscores.Num() > 50) {
				break;
			}
		}
	}

	UGameplayStatics::SaveGameToSlot(NewSave, SaveSlotName, 0);
}

UMySaveGame *UMySaveGame::LoadSave() {
	UMySaveGame *OldSave = Cast<UMySaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, 0));

	return OldSave;
}
