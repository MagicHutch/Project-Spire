// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerControllerV2.h"
#include "CharacterStats.h"

// Sets default values for this component's properties
UCharacterStats::UCharacterStats()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCharacterStats::BeginPlay()
{
	Super::BeginPlay();

	// ...

	//Configure status conditions list
	appliedStatusConditions.Add(StatusCondition::DESPAIR, false);
	appliedStatusConditions.Add(StatusCondition::TORMENT, false);
	appliedStatusConditions.Add(StatusCondition::CLANGRENE, false);
}


// Called every frame
void UCharacterStats::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//DESPAIR LOGIC

	if (currentDespair > 0) {
		currentDespair -= despairDecreasePerSecond * DeltaTime;
		
		if (currentDespair <= 0) {
			appliedStatusConditions.Add(StatusCondition::DESPAIR, false);
		}

		currentDespair = FMath::Clamp(currentDespair, 0, maximumDespair);
	}

	if (appliedStatusConditions.FindRef(StatusCondition::DESPAIR)) {
		currentHealth -= despairHealthPerSecond * DeltaTime;

		APlayerControllerV2* tryGetPlayer = Cast<APlayerControllerV2>(GetOwner());
		if (tryGetPlayer != nullptr) {
			tryGetPlayer->temporaryWill -= despairHealthPerSecond * DeltaTime;
		}
	}

	// ...
}

bool UCharacterStats::UseStamina(float staminaAmount)
{
	if (currentStamina > 0) {
		currentStamina -= staminaAmount;	
		currentStamina = FMath::Clamp(currentStamina, -1 * maximumStamina, maximumStamina);

		return true;
	}
	else {
		return false;
	}
}

void UCharacterStats::IncreaseDespairMeter(float amountToIncrease)
{
	currentDespair += amountToIncrease;

	if (currentDespair >= maximumDespair) {
		appliedStatusConditions.Add(StatusCondition::DESPAIR, true);
	}

	currentDespair = FMath::Clamp(currentDespair, 0, maximumDespair);
}
