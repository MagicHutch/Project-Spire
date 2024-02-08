// Fill out your copyright notice in the Description page of Project Settings.


#include "GaolSpearGuardV2.h"
#include "cmath"
#include "math.h"

// Sets default values
AGaolSpearGuardV2::AGaolSpearGuardV2()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGaolSpearGuardV2::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AGaolSpearGuardV2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AGaolSpearGuardV2::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float AGaolSpearGuardV2::AngleBetweenVectors(FVector v1, FVector v2, FVector rv)
{	
	//get the angle between forward and the test vector
	float dotProduct = v1.X * v2.X + v1.Y * v2.Y + v1.Z * v2.Z;
	float magnitude1 = sqrt(v1.X * v1.X + v1.Y * v1.Y + v1.Z * v1.Z);
	float magnitude2 = sqrt(v2.X * v2.X + v2.Y * v2.Y + v2.Z * v2.Z);

	//get the angle between the right and the test vector
	float magnitudeRight = sqrt(rv.X * rv.X + rv.Y * rv.Y + rv.Z * rv.Z);

	float result = dotProduct / (magnitude1 * magnitude2);
	float radianAngle = acos(result);

	return radianAngle * (180/3.14f);
}

GaolSpearGuardActions AGaolSpearGuardV2::SelectAction(float currentStamina, float currentHP, float maxHP, float playerHP, float playerMaxHP)
{
	//determine situation and advantage, to decide action
	float advantage = (currentHP / maxHP) - (playerHP / playerMaxHP);
	int test = 1;
	
	UE_LOG(LogTemp, Warning, TEXT("Advantage is %f %f %f %f"), currentHP, maxHP, playerHP, playerMaxHP);

	if (advantage < -0.2f) {
		return STRAFE;
	}
	else if (advantage < 0.2f) {
		return THRUST;
	}
	else {
		return SWING;
	}
}

