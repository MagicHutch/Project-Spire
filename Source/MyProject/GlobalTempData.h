// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PlayerControllerV2.h"
#include "EnemyCharacter.h"
#include "UsableWeapon.h"
#include "ConsumableItem.h"
#include "GlobalTempData.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API UGlobalTempData : public UGameInstance
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
		void SetDefaultValues();
	
	UFUNCTION(BlueprintCallable)
		void PlayerDeathDataClear();
	
	UFUNCTION(BlueprintCallable)
		void LoadPlayerStateFromTemporaryData(UPlayerInventory* inventoryObjectToWrite);

	UFUNCTION(BlueprintCallable)
		void WritePlayerStateToTemporaryData(UPlayerInventory* inventoryObjectToCopy);

	/////////////////////////////////////////////////////////////////////

	//VARIABLES

	/////////////////////////////////////////////////////////////////////
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		APlayerControllerV2* player;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TArray<AEnemyCharacter*> enemiesInScene;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TArray<TSubclassOf<AUsableWeapon>> playerWeaponList;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TArray<TSubclassOf<AUsableWeapon>> playerEquippedWeaponList;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TArray<AConsumableItem*> playerConsumableList;

	//////////////////////////////////////////////////////////////////////

	//SETTINGS

	//////////////////////////////////////////////////////////////////////
	UPROPERTY(BlueprintReadOnly)
		bool isFirstLoad = true;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FVector2D cameraSpeedModifier;

};
