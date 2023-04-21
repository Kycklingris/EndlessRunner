// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPlatform.h"
#include "../EndlessRunnerGameMode.h"
#include "EndlessRunnerGameState.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMyPlatform::AMyPlatform() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
}

// Called when the game starts or when spawned
void AMyPlatform::BeginPlay() {
	Super::BeginPlay();

	GameMode = Cast<AEndlessRunnerGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	GameState = GetWorld()->GetGameState<AEndlessRunnerGameState>();
}

// Called every frame
void AMyPlatform::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	if (GameMode == nullptr) {
		return;
	}

	auto Location = GetActorLocation();
	SetActorLocation(FVector(Location.X - (GameMode->PlatformMoveSpeed * GameState->SpeedModifier), 0.f, 0.f));

	if ((Location.X + (GetLength() / 2.f)) < GameMode->StartingPoint) {
		GameMode->UpdateLength(-GetLength());
		Destroy();
	}
}

float AMyPlatform::GetLength() {
	if (Length > 0) {
		return Length;
	}

	FVector BoxExtent;
	FVector Origin;
	GetActorBounds(false, Origin, BoxExtent, true);
	Length = BoxExtent.X * 2.f;

	return Length;
}