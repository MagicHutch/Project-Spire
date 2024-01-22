// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerScript.h"
#include "Camera/CameraComponent.h"

// Sets default values
APlayerScript::APlayerScript()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlayerScript::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerScript::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerScript::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APlayerScript::SpawnActor(TSubclassOf<AActor> actorToSpawn)
{
	FActorSpawnParameters spawnParams;
	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	GetWorld()->SpawnActor<AActor>(actorToSpawn, GetActorTransform(), spawnParams);
}

bool APlayerScript::IsOnScreen(FVector2D screenSize, FVector2D objectProjection)
{
	if (objectProjection.X >= 0 && objectProjection.X <= screenSize.X && objectProjection.Y >= 0 && objectProjection.Y <= screenSize.Y) {
		return true;
	}
	else {
		return false;
	}
}