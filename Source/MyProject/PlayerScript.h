// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerScript.generated.h"

UCLASS()
class MYPROJECT_API APlayerScript : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerScript();

	UFUNCTION(BlueprintCallable, Category = "Scripted Functions")
		void SpawnActor(class TSubclassOf<AActor> actorToSpawn);

	UFUNCTION(BlueprintCallable, Category = "Scripted Functions")
		bool IsOnScreen(FVector2D screenSize, FVector2D objectProjection);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
