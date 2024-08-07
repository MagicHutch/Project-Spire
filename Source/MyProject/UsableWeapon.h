// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/Texture.h"
#include "UsableItem.h"
#include "UsableWeapon.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API AUsableWeapon : public AUsableItem
{
	GENERATED_BODY()

	public:

		AUsableWeapon();

		UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
			void ActivateAttack();

		UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
			void DeactivateAttack();

		UFUNCTION(BlueprintCallable)
			void EnableWeapon();
		
		UFUNCTION(BlueprintCallable)
			void DisableWeapon();

		UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
			void AlterLevel();

		UPROPERTY(BlueprintReadWrite, EditAnywhere, Meta = (ExposeOnSpawn = "true"))
			AActor* weaponOwner;

		UPROPERTY(BlueprintReadWrite, EditAnywhere)
			UAnimMontage* weaponAnim;

		UPROPERTY(BlueprintReadWrite, EditAnywhere)
			UAnimMontage* offhandWeaponAnim;
		
		UPROPERTY(BlueprintReadWrite, EditAnywhere)
			UAnimMontage* skillWeaponAnim;

		UPROPERTY(BlueprintReadWrite, EditAnywhere)
			FVector hitboxOffset;

		UPROPERTY(BlueprintReadWrite, EditAnywhere)
			float baseDamage = 0;

		UPROPERTY(BlueprintReadWrite, EditAnywhere)
			bool isCharged = false;

		UPROPERTY(BlueprintReadWrite, EditAnywhere)
			int weaponLevel = 0;
		
		UPROPERTY(BlueprintReadWrite, EditAnywhere)
			int weaponDamageUpPerLevel = 0;
		
		UPROPERTY(BlueprintReadWrite, EditAnywhere)
			TArray<FString> weaponLevelDescriptions;

		//NEW ATTACK SYSTEM VARIABLES
			//0 = swing, 1 = stab
		UPROPERTY(BlueprintReadWrite, EditAnywhere)
			float weaponStaminaCost = 0;
		
		UPROPERTY(BlueprintReadWrite, EditAnywhere)
			int weaponDefaultSequence = 0;
		
		UPROPERTY(BlueprintReadWrite, EditAnywhere)
			bool isUsingAlternateSequence = false;

		UPROPERTY(BlueprintReadWrite, EditAnywhere)
			TArray<UAnimMontage*> rightSwingSequence;
		
		UPROPERTY(BlueprintReadWrite, EditAnywhere)
			TArray<UAnimMontage*> rightStabSequence;
		
		UPROPERTY(BlueprintReadWrite, EditAnywhere)
			UAnimMontage* rightHeavySwingAnim;
		
		UPROPERTY(BlueprintReadWrite, EditAnywhere)
			UAnimMontage* rightHeavyStabAnim;
		
		UPROPERTY(BlueprintReadWrite, EditAnywhere)
			UAnimMontage* rightDodgeSwingAnim;
		
		UPROPERTY(BlueprintReadWrite, EditAnywhere)
			UAnimMontage* rightDodgeStabAnim;
		
		UPROPERTY(BlueprintReadWrite, EditAnywhere)
			UAnimMontage* rightFallingAttackRecoveryAnim;
};
