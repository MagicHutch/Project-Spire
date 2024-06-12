// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnemyAction.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable )
class MYPROJECT_API UEnemyAction : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEnemyAction();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void UseAction();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void AttackBeginEvent();
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void AttackEndEvent();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float staminaCost = 10;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool isActiveState = false;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool canRegainStamina = false;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Attack Variables")
		bool isAttackAction = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Attack Variables")
		int attackSection = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Attack Variables")
		int attackTypeForOwner = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Attack Variables")
		bool ownerIsAttacking = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Attack Variables")
		float optimalAdvantage = 0;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Attack Variables")
		int bossPhase = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Attack Variables")
		TArray<AActor*> ignoreActorsList;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool canRotate = false;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float maxRotationSpeed = 0;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
