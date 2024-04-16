// Fill out your copyright notice in the Description page of Project Settings.


#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
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

void APlayerControllerV2::SnapToMoveDirection(FVector2D inputDirection, bool isLockedOn)
{
	//construct 3d move direction
	FVector moveDirection = FVector(inputDirection.X, inputDirection.Y, 0);

	//get player vectors
	FVector forwardVector = FVector(0,1,0);
	FVector rightVector = FVector(1,0,0);
	
	//snap player rotation
	float degreesToRotate = AngleBetweenVectors(forwardVector, moveDirection, rightVector);
	float yawRotation = degreesToRotate + GetActorRotation().Yaw;

	//UE_LOG(LogTemp, Warning, TEXT("Rotating: %f"), GetActorRotation().Yaw);
	//UE_LOG(LogTemp, Warning, TEXT("Rotating: %f"), degreesToRotate);

	GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor::Red, FString::Printf(TEXT("Rotation: %f"), GetActorRotation().Yaw));
	GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor::Red, FString::Printf(TEXT("Amount To Rotate: %f"), degreesToRotate));

	if (isLockedOn) {
		SetActorRotation(FRotator(0, yawRotation, 0));
	}
	else {
		//SetActorRotation(FRotator(0, yawRotation + GetActorRotation().Yaw, 0));
	}

	return;
}