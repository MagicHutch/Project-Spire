// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterStats.generated.h"

UENUM(BlueprintType)
enum class StatusCondition : uint8
{
	DESPAIR = 0,
	TORMENT = 1,
	CLANGRENE = 2
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYPROJECT_API UCharacterStats : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCharacterStats();

	//UPDATE FUNCTIONS
	UFUNCTION(BlueprintCallable, Category = "Scripted Functions")
		bool UseStamina(float staminaAmount);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void PlayerTemporaryHealthAdjust(float healthDecrease);

	UFUNCTION(BlueprintCallable, Category = "Scripted Functions")
		void IncreaseDespairMeter(float amountToIncrease);

	//STATS
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float currentHealth = 100;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float maximumHealth = 100;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float currentStamina = 100;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float maximumStamina = 100;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float staminaPerSecond = 50;

	//STATUS CONDITIONS
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TMap<StatusCondition, bool> appliedStatusConditions;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float currentDespair = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float maximumDespair = 100;
	
	UPROPERTY(BlueprintReadOnly)
		float despairDecreasePerSecond = 2.5f;

	UPROPERTY(BlueprintReadOnly)
		float despairHealthPerSecond = 2.5f;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
