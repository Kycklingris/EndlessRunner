// Fill out your copyright notice in the Description page of Project Settings.

#include "MyAICharacter.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

AMyAICharacter::AMyAICharacter() {
	AICollider = CreateDefaultSubobject<UBoxComponent>(TEXT("AICollider"));
	AICollider->SetCollisionProfileName(FName("Trigger"));
	AICollider->SetGenerateOverlapEvents(false);

	TScriptDelegate<FWeakObjectPtr> OnAIObstacleBeginOverlapDelegate;
	OnAIObstacleBeginOverlapDelegate.BindUFunction(this, "OnAIObstacleBeginOverlap");
	AICollider->OnComponentBeginOverlap.Add(OnAIObstacleBeginOverlapDelegate);

	AICollider->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AMyAICharacter::BeginPlay() {
	Super::BeginPlay();
}

void AMyAICharacter::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent) {
	// Overrides so nothing happens
}

void AMyAICharacter::OnAIObstacleBeginOverlap(UPrimitiveComponent *OverlappedComp, AActor *OtherActor,
	UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult) {
	float Time = UGameplayStatics::GetRealTimeSeconds(GetWorld());

	if (LastOverlapEvent + TimeBetweenOverlaps > Time) {
		return;
	}
	LastOverlapEvent = Time;

	// if (GEngine) {
	// 	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Some debug message!"));
	// }

	if (Position < 0) {
		Move_Right();
	} else {
		Move_Left();
	}
}