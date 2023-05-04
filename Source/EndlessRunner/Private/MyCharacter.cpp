// Fill out your copyright notice in the Description page of Project Settings.

#include "MyCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInput/Public/InputAction.h"
#include "EnhancedInput/Public/EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EndlessRunnerGameState.h"
#include "MySaveGame.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMyCharacter::AMyCharacter() {
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need
	// it.
	PrimaryActorTick.bCanEverTick = true;

	UCapsuleComponent *Collider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collider"));
	Collider->SetCollisionProfileName(FName("CharacterMesh"));
	Collider->SetGenerateOverlapEvents(true);

	TScriptDelegate<FWeakObjectPtr> OnObstacleBeginOverlapDelegate;
	OnObstacleBeginOverlapDelegate.BindUFunction(this, "OnObstacleBeginOverlap");
	Collider->OnComponentBeginOverlap.Add(OnObstacleBeginOverlapDelegate);

	TScriptDelegate<FWeakObjectPtr> OnObstacleHitDelegate;
	OnObstacleHitDelegate.BindUFunction(this, "OnObstacleHit");
	Collider->OnComponentHit.Add(OnObstacleHitDelegate);

	RootComponent = Collider;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay() {
	Super::BeginPlay();

	Health = 3;

	auto Location = GetActorLocation();
	YOffset = Location.Y;
	if (Position == -1) {
		Location.Y = YOffset + -50.f;
	} else {
		Location.Y = YOffset + 50.f;
	}
	SetActorLocation(Location);
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	Points += PointsPerMinute * DeltaTime / 60.f;
}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent) {
	if (UEnhancedInputComponent *PlayerEnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		// There are ways to bind a UInputAction* to a handler function and multiple types of ETriggerEvent that may be
		// of interest.

		// This calls the handler function on the tick when MyInputAction starts, such as when pressing an action
		// button.
		if (LeftAction) {
			PlayerEnhancedInputComponent->BindAction(
				LeftAction, ETriggerEvent::Started, this, &AMyCharacter::Input_Move_Left);
		}

		// This calls the handler function (a UFUNCTION) by name on every tick while the input conditions are met, such
		// as when holding a movement key down.
		if (RightAction) {
			PlayerEnhancedInputComponent->BindAction(
				RightAction, ETriggerEvent::Started, this, &AMyCharacter::Input_Move_Right);
		}
	}

	// Make sure that we have a valid PlayerController.
	if (APlayerController *PC = Cast<APlayerController>(GetController())) {
		// Get the Enhanced Input Local Player Subsystem from the Local Player related to our Player Controller.
		if (UEnhancedInputLocalPlayerSubsystem *Subsystem =
				ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer())) {
			// PawnClientRestart can run more than once in an Actor's lifetime, so start by clearing out any leftover
			// mappings.
			Subsystem->ClearAllMappings();

			// Add each mapping context, along with their priority values. Higher values outprioritize lower values.
			Subsystem->AddMappingContext(MappingContext, 0);
		}
	}
}

void AMyCharacter::Input_Move_Right(const FInputActionValue &InputActionValue) {
	Move_Right();
}

void AMyCharacter::Input_Move_Left(const FInputActionValue &InputActionValue) {
	Move_Left();
}

void AMyCharacter::Move_Left() {
	Position = -1;
	auto Location = GetActorLocation();
	Location.Y = YOffset + -50.f;
	SetActorLocation(Location);
}

void AMyCharacter::Move_Right() {
	Position = 1;
	auto Location = GetActorLocation();
	Location.Y = YOffset + 50.f;
	SetActorLocation(Location);
}

void AMyCharacter::OnObstacleBeginOverlap(UPrimitiveComponent *OverlappedComp, AActor *OtherActor,
	UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult) {
}

void AMyCharacter::OnObstacleHit(UPrimitiveComponent *HitComp, AActor *OtherActor, UPrimitiveComponent *OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult) {

	auto Location = GetActorLocation();

	Position *= -1;
	Location.Y = YOffset + 50.f * Position;

	SetActorLocation(Location);

	UpdateHealth(-1);
}

void AMyCharacter::UpdateHealth(int Modifier) {
	float Time = UGameplayStatics::GetRealTimeSeconds(GetWorld());
	if (LastHit + TimeBetweenHits > Time) {
		return;
	}

	LastHit = Time;

	Health += Modifier;
	// if (Health <= 0) {
	// 	int Points = (int)Points;
	// 	UMySaveGame::SaveScore(Points);

	// 	UGameplayStatics::OpenLevel(GetWorld(), FName("MainMenuLevel"));
	// }
}
