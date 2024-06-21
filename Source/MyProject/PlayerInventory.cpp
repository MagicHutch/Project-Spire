// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerInventory.h"

// Sets default values for this component's properties
UPlayerInventory::UPlayerInventory()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	leftWeaponsEquipped.Add(nullptr);
	leftWeaponsEquipped.Add(nullptr);
	leftWeaponsEquipped.Add(nullptr);

	rightWeaponsEquipped.Add(nullptr);
	rightWeaponsEquipped.Add(nullptr);
	rightWeaponsEquipped.Add(nullptr);

	leftWeaponSlot = 0;
	rightWeaponSlot = 0;

	for (int i = 0; i < 5; i++) {
		consumablesEquipped.Add(nullptr);
	}

	consumableSlot = 0;
	// ...
}


// Called when the game starts
void UPlayerInventory::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UPlayerInventory::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UPlayerInventory::CreateInventoryObjects(TArray<UClass*> weaponsToCreate)
{
	FTransform spawnTransform;

	for (int i = 0; i < weaponsToCreate.Num(); i++) {
		FActorSpawnParameters spawnParams;
		spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		weaponList.Add(Cast<AUsableWeapon>(GetWorld()->SpawnActor<AActor>(weaponsToCreate[i], spawnTransform, spawnParams)));
	}
}

void UPlayerInventory::SortIncomingObject(TSubclassOf<AUsableItem> objectToSort, int quantity)
{
	AUsableItem* defaultActor = Cast<AUsableItem>(objectToSort->GetDefaultObject());

	if (defaultActor->itemType == "CONSUMABLE") {
		TSubclassOf<AConsumableItem> objectClass = defaultActor->GetClass();

		for (auto it : consumableList) {
			if (it.Key == objectClass) {
				consumableList[objectClass] += quantity;
				return;
			}
		}

		consumableList.Add(objectClass, quantity);
		return;
	}

	else if (defaultActor->itemType == "WEAPON") {
		for (int i = 0; i < quantity; i++) {
			//create the weapon from the given class
			FActorSpawnParameters spawnParams;
			spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
			FTransform blankTransform;
			AUsableWeapon* spawnedWeapon = Cast<AUsableWeapon>(GetWorld()->SpawnActor<AActor>(objectToSort, blankTransform, spawnParams));

			//add it to weapon list
			weaponList.Add(spawnedWeapon);

			//turn off rendering and tick on spawned weapon to decrease resource use
			spawnedWeapon->SetActorHiddenInGame(true);
			spawnedWeapon->SetActorTickEnabled(false);
		}

		return;
	}
}

void UPlayerInventory::SwitchLeftWeapon()
{
	if (leftWeaponsEquipped[leftWeaponSlot] != nullptr) {
		leftWeaponsEquipped[leftWeaponSlot]->DisableWeapon();
	}

	leftWeaponSlot++;
	if (leftWeaponSlot > 2) {
		leftWeaponSlot = 0;
	}

	if (leftWeaponsEquipped[leftWeaponSlot] != nullptr) {
		leftWeaponsEquipped[leftWeaponSlot]->EnableWeapon();
	}
}

void UPlayerInventory::SwitchRightWeapon()
{
	if (rightWeaponsEquipped[rightWeaponSlot] != nullptr) {
		rightWeaponsEquipped[rightWeaponSlot]->DisableWeapon();
	}

	rightWeaponSlot++;
	if (rightWeaponSlot > 2) {
		rightWeaponSlot = 0;
	}

	if (rightWeaponsEquipped[rightWeaponSlot] != nullptr) {
		rightWeaponsEquipped[rightWeaponSlot]->EnableWeapon();
	}
}

void UPlayerInventory::SwapWeaponHands()
{
	AUsableWeapon* leftPlaceholder = leftWeaponsEquipped[leftWeaponSlot];

	leftWeaponsEquipped[leftWeaponSlot] = rightWeaponsEquipped[rightWeaponSlot];
	rightWeaponsEquipped[rightWeaponSlot] = leftPlaceholder;
}