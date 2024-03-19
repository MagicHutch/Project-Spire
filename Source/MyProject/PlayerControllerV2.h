// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterStats.h"
#include "GameFramework/Character.h"
#include "PlayerControllerV2.generated.h"

UCLASS()
class MYPROJECT_API APlayerControllerV2 : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerControllerV2();

	UFUNCTION(BlueprintCallable, Category = "Scripted Functions")
		bool IsOnScreen(FVector2D screenSize, FVector2D objectProjection);

	UFUNCTION(BlueprintCallable, Category = "Scripted Functions")
		float AngleBetweenVectors(FVector v1, FVector v2, FVector rv);

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UCharacterStats* stats;
	
	//UPROPERTY(BlueprintReadWrite, EditAnywhere)
		//TArray<

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
