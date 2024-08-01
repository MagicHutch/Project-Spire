// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UsableItem.h"
#include "PlayerSpecialSkill.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API APlayerSpecialSkill : public AUsableItem
{
	GENERATED_BODY()
	
	public:

	APlayerSpecialSkill();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void UseSkill();
	
	UFUNCTION(BlueprintCallable)
		void ToggleObjectTick(bool canTick);
	
	UFUNCTION(BlueprintCallable)
		void ToggleObjectVisibility(bool isVisible);
	
	UFUNCTION(BlueprintCallable)
		void ToggleIsEquipped(bool isEquipped);

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool tickEnabledOnSpawn = false;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool isVisibleOnSpawn = false;
	
	UPROPERTY(blueprintReadWrite, EditAnywhere)
		bool tickEnabledWhenEquipped = false;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool isVisibleWhenEquipped = false;
};
