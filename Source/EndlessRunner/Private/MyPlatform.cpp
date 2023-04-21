// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPlatform.h"

// Sets default values
AMyPlatform::AMyPlatform() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
}

// Called when the game starts or when spawned
void AMyPlatform::BeginPlay() {
	Super::BeginPlay();

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