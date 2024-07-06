// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UsableItem.h"
#include "LevelKey.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API ALevelKey : public AUsableItem
{
	GENERATED_BODY()
	
public:
	
	ALevelKey();
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FString keyDoorTag;

};
