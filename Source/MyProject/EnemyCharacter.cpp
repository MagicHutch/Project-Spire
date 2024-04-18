// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"
#include "CharacterStats.h"

// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	stats = CreateDefaultSubobject<UCharacterStats>(TEXT("Enemy Stats"));
}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float AEnemyCharacter::AngleBetweenVectors(FVector v1, FVector v2)
{	
	//get the angle between forward and the test vector
	float dotProduct = v1.X * v2.X + v1.Y * v2.Y + v1.Z * v2.Z;
	float magnitude1 = v1.Length();
	float magnitude2 = v2.Length();

	float result = dotProduct / (magnitude1 * magnitude2);
	float radianAngle = acos(result);

	return radianAngle * (180/3.14f);
}

bool AEnemyCharacter::NextState(UEnemyAction* inputState)
{
	if (inputState != nullptr) {
		if (inputState->staminaCost <= stats->currentStamina) {
			if (currentState != nullptr) {
				currentState->isActiveState = false;
			}
			
			currentState = inputState;
			currentState->isActiveState = true;
			stats->currentStamina -= currentState->staminaCost;
			currentState->UseAction();

			return true;
		}

		else {
			return false;
		}
	}
	else {
		return false;
	}
}

UEnemyAction* AEnemyCharacter::PickNextAction(float currentAdvantage, TArray<UEnemyAction*> actionList)
{
	if (actionList.Num() > 0) {
		TArray<UEnemyAction*> attackList;

		for (int i = 0; i < actionList.Num(); i++) {
			if (actionList[i]->isAttackAction) {
				attackList.Add(actionList[i]);
			}
		}

		if (attackList.Num() > 0) {
			float bestScore = 10;
			UEnemyAction* bestAction = nullptr;

			for (int i = 0; i < attackList.Num(); i++) {
				float testScore = abs(attackList[i]->optimalAdvantage - currentAdvantage);

				UE_LOG(LogTemp, Warning, TEXT("Action: %s, TestScore: %f"), attackList[i], testScore);

				if (testScore < bestScore) {
					bestScore = testScore;
					bestAction = attackList[i];
				}
			}	

			return bestAction;
		}
		else {
			return nullptr;
		}
	}
	else {
		return nullptr;
	}
}