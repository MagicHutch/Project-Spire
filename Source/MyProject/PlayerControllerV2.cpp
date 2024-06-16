// Fill out your copyright notice in the Description page of Project Settings.


#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Math/Vector.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Camera/CameraComponent.h"
#include "PlayerControllerV2.h"

// Sets default values
APlayerControllerV2::APlayerControllerV2()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	stats = CreateDefaultSubobject<UCharacterStats>(TEXT("Enemy Stats"));
}

// Called when the game starts or when spawned
void APlayerControllerV2::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerControllerV2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerControllerV2::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

bool APlayerControllerV2::IsOnScreen(FVector2D screenSize, FVector2D objectProjection)
{
	if (objectProjection.X >= 0 && objectProjection.X <= screenSize.X && objectProjection.Y >= 0 && objectProjection.Y <= screenSize.Y) {
		return true;
	}
	else {
		return false;
	}
}

void APlayerControllerV2::SnapToMoveDirection(FVector2D inputDirection, bool isLockedOn)
{
	UCameraComponent* playerCamera = GetComponentByClass<UCameraComponent>();
	
	//construct 3d move direction
	FVector moveDirection = FVector(inputDirection.X, inputDirection.Y, 0);
	FVector cameraForwardVector = playerCamera->GetForwardVector();
	FVector cameraRightVector = playerCamera->GetRightVector();
	cameraForwardVector.Z = 0;
	cameraRightVector.Z = 0;

	//get player vectors
	FVector forwardVector = FVector(0,1,0);
	FVector rightVector = FVector(1,0,0);
	
	//snap player rotation
	float degreesToRotate = AngleBetweenVectors(forwardVector, moveDirection, rightVector);
	float yawRotation = degreesToRotate + GetActorRotation().Yaw;

	float degreesToSnap = AngleBetweenVectors(cameraForwardVector, moveDirection, cameraRightVector);
	float yawSnapRotation = GetActorRotation().Yaw + degreesToSnap;

	//UE_LOG(LogTemp, Warning, TEXT("Rotating: %f"), GetActorRotation().Yaw);
	//UE_LOG(LogTemp, Warning, TEXT("Rotating: %f"), degreesToRotate);

	GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor::Red, FString::Printf(TEXT("Rotation: %f"), GetActorRotation().Yaw));
	GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor::Red, FString::Printf(TEXT("Amount To Rotate: %f"), degreesToSnap));

	if (isLockedOn) {
		SetActorRotation(FRotator(0, yawRotation, 0));
	}
	else {
		SetActorRotation(FRotator(0, yawSnapRotation, 0));
	}

	return;
}

/////////////////////////////////////////////////////////////////////////////////

//BASIC FUNCTIONS

/////////////////////////////////////////////////////////////////////////////////

float APlayerControllerV2::AngleBetweenVectors(FVector v1, FVector v2, FVector rv)
{	
	//get the angle between forward and the test vector
	float dotProduct = v1.X * v2.X + v1.Y * v2.Y + v1.Z * v2.Z;
	float magnitude1 = sqrt(v1.X * v1.X + v1.Y * v1.Y + v1.Z * v1.Z);
	float magnitude2 = sqrt(v2.X * v2.X + v2.Y * v2.Y + v2.Z * v2.Z);
	float result = dotProduct / (magnitude1 * magnitude2);

	//get the angle between the right and the test vector
	float rightDotProduct = v2.X * rv.X + v2.Y * rv.Y + v2.Z * rv.Z;
	float magnitudeRight = sqrt(rv.X * rv.X + rv.Y * rv.Y + rv.Z * rv.Z);
	float signResult = rightDotProduct / (magnitude2 * magnitudeRight);

	float radianAngle = acos(result);
	float rightRadianAngle = acos(signResult);
	
	if (rightRadianAngle * (180/3.1415f) < 90) {
		return radianAngle * (180/3.1415f);
	}
	else {
		return radianAngle * (180/3.1415f) * -1;
	}
}

float APlayerControllerV2::RawAngleBetweenVectors(FVector v1, FVector v2)
{
	//get the angle between forward and the test vector
	float dotProduct = v1.X * v2.X + v1.Y * v2.Y + v1.Z * v2.Z;
	float magnitude1 = v1.Length();
	float magnitude2 = v2.Length();

	float result = dotProduct / (magnitude1 * magnitude2);
	float radianAngle = acos(result);

	return radianAngle * (180/PI);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Lock-on related functions
//lock for selecting which enemy to lock on to, and for contgrolling switching between targets

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

AActor* APlayerControllerV2::EvaluateLockOnOptions(TArray<AActor*> allEnemies, TArray<TEnumAsByte<EObjectTypeQuery>> objectTypesList)
{
	if (allEnemies.Num() > 0) {
		GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor::Red, FString::Printf(TEXT("%i Enemies In Scene"), allEnemies.Num()));

		//narrow list to actors within FOV
		TMap<AActor*,float> allEnemiesWithinView;

		UCameraComponent* playerCamera = GetComponentByClass<UCameraComponent>();

		FVector selfLocation = playerCamera->GetComponentTransform().GetLocation();
		FVector selfForwardVector = playerCamera->GetForwardVector();

		TArray<AActor*> actorsToIgnoreList;

		for (AActor* index : allEnemies) {
			//check if target is within FOV
			FVector indexLocation = index->GetActorLocation();
			FVector vectorToIndex = indexLocation - selfLocation;
			float angleToIndex = RawAngleBetweenVectors(selfForwardVector, vectorToIndex);

			//check if player has line of sight to potential target
			FHitResult hitResult;
			bool viewIsBlocked = UKismetSystemLibrary::LineTraceSingleForObjects(this, selfLocation, indexLocation, objectTypesList, true, actorsToIgnoreList, EDrawDebugTrace::None, hitResult, true, FLinearColor::Red, FLinearColor::Green, 0);

			if (angleToIndex < 60 && !viewIsBlocked) {
				allEnemiesWithinView.Add(index, angleToIndex);
			}
		}

		GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor::Red, FString::Printf(TEXT("Lock On Options: %i"), allEnemiesWithinView.Num()));

		if (allEnemiesWithinView.Num() > 0) {
			allEnemiesWithinView.ValueSort([](int32 A, int32 B) {return A < B;});
			TArray<AActor*> enemiesWithinViewKeyArray;
			allEnemiesWithinView.GenerateKeyArray(enemiesWithinViewKeyArray);
			return enemiesWithinViewKeyArray[0];
		}
		
		//if no valid targets, return null
		else {
			return nullptr;
		}
	}

	//if no enemies in view, return null
	else {
		return nullptr;
	}
}

AActor* APlayerControllerV2::ProcessSwitchLockOn(FVector2D referencePosition, TArray<AActor*> allEnemies, TArray<TEnumAsByte<EObjectTypeQuery>> objectTypesList, FVector2D processDirection, FVector2D screenSize, AActor* currentLockOn)
{
	if (allEnemies.Num() > 0 && processDirection.Length() > 0.10f) {
		processDirection.Normalize();

		GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor::Red, FString::Printf(TEXT("%i Enemies In Scene"), allEnemies.Num()));

		//store screen size
		FVector2D screenCenter; screenCenter.X = screenSize.X / 2; screenCenter.Y = screenSize.Y / 2;
		

		//narrow list to actors within FOV
		TArray<AActor*> allEnemiesWithinView;

		UCameraComponent* playerCamera = GetComponentByClass<UCameraComponent>();
		APlayerController* playerController = GetWorld()->GetFirstPlayerController();

		FVector selfLocation = playerCamera->GetComponentTransform().GetLocation();
		FVector selfForwardVector = playerCamera->GetForwardVector();

		TArray<AActor*> actorsToIgnoreList;

		for (AActor* index : allEnemies) {
			if (index != nullptr) {
				//check if target is within FOV
				FVector indexLocation = index->GetActorLocation();
				FVector vectorToIndex = indexLocation - selfLocation;
				float angleToIndex = RawAngleBetweenVectors(selfForwardVector, vectorToIndex);

				//check if player has line of sight to potential target
				FHitResult hitResult;
				bool viewIsBlocked = UKismetSystemLibrary::LineTraceSingleForObjects(this, selfLocation, indexLocation, objectTypesList, true, actorsToIgnoreList, EDrawDebugTrace::None, hitResult, true, FLinearColor::Red, FLinearColor::Green, 0);

				if (angleToIndex < 40 && !viewIsBlocked) {
					allEnemiesWithinView.Add(index);
				}
			}
		}

		GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor::Red, FString::Printf(TEXT("Lock On Options: %i"), allEnemiesWithinView.Num()));

		TMap<AActor*, float> enemiesInDirection;

		allEnemiesWithinView.Remove(currentLockOn);

		if (allEnemiesWithinView.Num() > 0) {
			for (AActor* index : allEnemiesWithinView) {
				FVector indexLocation = index->GetActorLocation();
				FVector2D indexScreenLocation;
				playerController->ProjectWorldLocationToScreen(indexLocation, indexScreenLocation, false);

				//get angle
				FVector2D enemyDirection = indexScreenLocation - referencePosition;
				float angle = acos(FVector2D::DotProduct(enemyDirection, processDirection) / (enemyDirection.Length() * processDirection.Length()));

				if (angle < 90) {
					enemiesInDirection.Add(index, angle * enemyDirection.Length());
				}
			}

			if (enemiesInDirection.Num() > 0) {
				enemiesInDirection.ValueSort([](int32 A, int32 B) {return A < B;});
				TArray<AActor*> keys;
				enemiesInDirection.GenerateKeyArray(keys);
				return keys[0];
			}
			else {
				return nullptr;
			}
		}
		
		//if no valid targets, return null
		else {
			return nullptr;
		}
	}

	//if no enemies in view, return null
	else {
		return nullptr;
	}
}