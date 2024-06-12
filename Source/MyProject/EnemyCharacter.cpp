// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"
#include "CharacterStats.h"
#include "Math/Vector.h"
#include "Math/UnrealMathUtility.h"

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

float AEnemyCharacter::AngleToPlayer()
{
	if (player != nullptr) {
		FVector vectorToPlayer = player->GetActorLocation() - GetActorLocation();
		FVector forwardVector = GetActorForwardVector();
		FVector rightVector = GetActorRightVector();

		float baseDotProduct = FVector::DotProduct(forwardVector, vectorToPlayer);
		float rightDotProduct = FVector::DotProduct(rightVector, vectorToPlayer);

		float angle = acos(baseDotProduct / (vectorToPlayer.Length() * forwardVector.Length())) * (180/PI);

		if (rightDotProduct * (180/PI) <= 90) {
			return angle;
		}
		else {
			return angle * -1;
		}
	}
	else {
		return 0;
	}
}

bool AEnemyCharacter::NextState(UEnemyAction* inputState, bool overrideQueue)
{
	
	if (actionQueue.Num() > 0 && !overrideQueue) {
		if (currentState != nullptr) {
			currentState->isActiveState = false;
			currentState->attackSection = 0;
		}

		currentState = actionQueue[0];
		currentState->isActiveState = true;
		stats->currentStamina -= currentState->staminaCost;
		currentState->UseAction();

		actionQueue.RemoveAt(0);

		return true;
	}

	else if (inputState != nullptr) {
		if (inputState->staminaCost <= stats->currentStamina) {
			if (currentState != nullptr) {
				currentState->isActiveState = false;
				currentState->attackSection = 0;
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

		//populate attackList with all of the attacking actions
		for (int i = 0; i < actionList.Num(); i++) {
			if (actionList[i]->isAttackAction && actionList[i]->bossPhase == currentPhase) {
				attackList.Add(actionList[i]);
			}
		}

		//if there are options in the attackList
		if (attackList.Num() > 0) {
			float averageDifference = 0;
			UEnemyAction* bestAction = nullptr;

			//find the mean difference from current advantage of attack options
			for (int i = 0; i < attackList.Num(); i++) {
				averageDifference += abs(attackList[i]->optimalAdvantage - currentAdvantage);
			}	

			averageDifference /= attackList.Num();

			TArray<UEnemyAction*> attacksToPick;

			//make a list of all attacks within the average distance
			for (int i = 0; i < attackList.Num(); i++) {
				if (abs(attackList[i]->optimalAdvantage - currentAdvantage) <= averageDifference) {
					attacksToPick.Add(attackList[i]);
				}
			}

			//return a random option from that
			return attacksToPick[FMath::RandRange(0,attacksToPick.Num()-1)];
		}
		else {
			return nullptr;
		}
	}
	else {
		return nullptr;
	}
}

TArray<UEnemyAction*> AEnemyCharacter::CreateActionSequence(TArray<UEnemyAction*> actionList)
{
	//Create a array to return once the sequence is created
	TArray<UEnemyAction*> sequenceToReturn;


	for (int i = 0; i < attackSlotChecklist.Num(); i++) {
		//create a list of actions in the current attack slot being evaluated
		TArray<UEnemyAction*> listToFeed;
		
		for (int j = 0; j < actionList.Num(); j++) {
			if (actionList[j]->attackTypeForOwner == i) {
				listToFeed.Add(actionList[j]);
			}
		}

		//pick an action to add to the sequence
		if (listToFeed.Num() > 0) {
			sequenceToReturn.Add(PickNextAction(advantage, listToFeed));
		}
	}

	//return the sequence of actions to execute

	if (sequenceToReturn.Num()) {
		for (int i = 0; i < sequenceToReturn.Num(); i++) {
			actionQueue.Add(sequenceToReturn[i]);
		}
	}

	NextState(actionQueue[0], false);

	return sequenceToReturn;
}