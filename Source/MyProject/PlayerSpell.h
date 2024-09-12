// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UsableItem.h"
#include "PlayerSpell.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API APlayerSpell : public AUsableItem
{
	GENERATED_BODY()
	
public:

	//assign default values for the class
	APlayerSpell();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void useSpell();
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void useSpellTick(float tickLength);
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void useSpellReleased();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void useSpellAbort();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void useSpellImmediate();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int spellCost = 0;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool isCurrentlyInUse = false;

	//PROJECTION, INTERSECTION, CONJURATION
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FString spellCategory = "";

};
