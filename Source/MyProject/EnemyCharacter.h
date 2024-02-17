// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerScript.h"
#include "CharacterStats.h"
#include "EnemyAction.h"
#include "EnemyCharacter.generated.h"

UCLASS()
class MYPROJECT_API AEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyCharacter();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void NextState(UEnemyAction* inputState);

	UFUNCTION(BlueprintCallable, Category = "Scripted Functions")
		float AngleBetweenVectors(FVector v1, FVector v2, FVector rv);

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		APlayerScript* player;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		UCharacterStats* stats;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UEnemyAction* entryState;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UEnemyAction* currentState;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TMap<int, UEnemyAction*> stateList;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FVector lockOnOffset;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float advantage;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
