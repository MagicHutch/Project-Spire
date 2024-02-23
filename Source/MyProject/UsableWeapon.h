// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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

		UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
			void ActivateAttack();

		UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
			void DeactivateAttack();

		UPROPERTY(BlueprintReadWrite, EditAnywhere)
			float baseDamage = 0;
	
};
