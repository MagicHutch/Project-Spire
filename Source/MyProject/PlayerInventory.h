// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UsableItem.h"
#include "UsableWeapon.h"
#include "ConsumableItem.h"
#include "LevelKey.h"
#include "PlayerInventory.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYPROJECT_API UPlayerInventory : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerInventory();

	UFUNCTION(BlueprintCallable, Category = "Scripted Functions")
		void CreateInventoryObjects(TArray<UClass*> weaponsToCreate);

	UFUNCTION(BlueprintCallable, Category = "Scripted Functions")
		void SortIncomingObject(TSubclassOf<AUsableItem> objectToSort, int quantity);

	UFUNCTION(BlueprintCallable, Category = "Scripted Functions")
		void SwitchRightWeapon();

	UFUNCTION(BlueprintCallable, Category = "Scripted Functions")
		void SwitchLeftWeapon();

	UFUNCTION(BlueprintCallable, Category = "Scripted Functions")
		void SwapWeaponHands();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TArray<AUsableWeapon*> weaponList;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TMap<TSubclassOf<AConsumableItem>, int> consumableList;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TArray<AUsableWeapon*> leftWeaponsEquipped;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TArray<AUsableWeapon*> rightWeaponsEquipped;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int leftWeaponSlot;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int rightWeaponSlot;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TArray<TSubclassOf<AConsumableItem>> consumablesEquipped;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int consumableSlot;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TArray<TSubclassOf<ALevelKey>> keyList;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
