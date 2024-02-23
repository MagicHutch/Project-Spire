// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UsableItem.h"
#include "ConsumableItem.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API AConsumableItem : public AUsableItem
{
	GENERATED_BODY()
	
	public:

		UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
			void UseItem();

};
