// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GaolSpearGuardAction.h"
#include "GaolSpearGuardV2.generated.h"

UENUM(BlueprintType)
enum GaolSpearGuardActions
{
	THRUST,
	SWING
};

UCLASS()
class MYPROJECT_API AGaolSpearGuardV2 : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGaolSpearGuardV2();

	//Functions
	UFUNCTION(BlueprintCallable, Category = "Scripted Functions")
		float AngleBetweenVectors(FVector v1, FVector v2, FVector rv);
	
	UFUNCTION(BlueprintCallable, Category = "Scripted Functions")
		GaolSpearGuardActions SelectAction(float currentStamina, float currentHP, float maxHP, float playerHP, float playerMaxHP);

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool canAct = true;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
