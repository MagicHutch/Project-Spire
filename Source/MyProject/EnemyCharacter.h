// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerControllerV2.h"
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

	//functions
	UFUNCTION(BlueprintCallable, Category = "Scripted Functions")
		bool NextState(UEnemyAction* inputState, bool overrideQueue);

	UFUNCTION(BlueprintCallable, Category = "Scripted Functions")
		float AngleBetweenVectors(FVector v1, FVector v2);

	UFUNCTION(BlueprintCallable, Category = "Scripted Functions")
		UEnemyAction* PickNextAction(float currentAdvantage, TArray<UEnemyAction*> actionList);

	UFUNCTION(BlueprintCallable, Category = "Scripted Functions")
		TArray<UEnemyAction*> CreateActionSequence(TArray<UEnemyAction*> actionList);

	UFUNCTION(BlueprintCallable, Category = "Scripted Functions")
		float AngleToPlayer();

	//references
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
		APlayerControllerV2* player;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		UCharacterStats* stats;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UEnemyAction* entryState;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UEnemyAction* currentState;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TArray<UEnemyAction*> actionQueue;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TMap<int, bool> attackSlotChecklist;

	//variables
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FVector lockOnOffset;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float advantage;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float wanderSpeed = 150;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float chaseSpeed = 300;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float fieldOfViewAngle = 65;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FVector anchorPosition;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool isAggro = false;

	//optional boss variables
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool isBoss;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FText bossName;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int currentPhase = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int orValue;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
