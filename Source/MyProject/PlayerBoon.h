// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UsableItem.h"
#include "PlayerBoon.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API APlayerBoon : public APlayerSpecialSkill
{
	GENERATED_BODY()
	
	public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float willCost = 0;
};
