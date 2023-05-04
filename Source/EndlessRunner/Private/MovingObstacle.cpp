// Fill out your copyright notice in the Description page of Project Settings.

#include "MovingObstacle.h"
#include "../EndlessRunnerGameMode.h"
#include "EndlessRunnerGameState.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"

// Sets default values
AMovingObstacle::AMovingObstacle() {
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	UBoxComponent *Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("RootComponent"));
	Collider->SetCollisionProfileName(FName("BlockAllDynamic"));

	DefaultRoot = Collider;
	RootComponent = DefaultRoot;

	Cube = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cube"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'"));
	UStaticMesh *Asset = MeshAsset.Object;
	Cube->SetStaticMesh(Asset);
	Cube->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AMovingObstacle::BeginPlay() {
	Super::BeginPlay();
}

// Called every frame
void AMovingObstacle::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	auto GameState = GetWorld()->GetGameState<AEndlessRunnerGameState>();

	auto Location = GetActorLocation();
	Location.X -= MovementSpeed * MovementSpeedMultipier * GameState->SpeedModifier * DeltaTime;
	SetActorLocation(Location, true);

	if (Location.X + GetLength() / 2.f < DespawnPoint) {
		Destroy();
	}
}

float AMovingObstacle::GetLength() {
	if (Length > 0) {
		return Length;
	}

	FVector BoxExtent;
	FVector Origin;
	GetActorBounds(false, Origin, BoxExtent, true);
	Length = BoxExtent.X * 2.f;

	return Length;
}