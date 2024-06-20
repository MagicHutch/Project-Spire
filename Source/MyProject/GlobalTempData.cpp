// Fill out your copyright notice in the Description page of Project Settings.


#include "GlobalTempData.h"

//used to make "starting points" for various settings, only run on initial load up of the game
void UGlobalTempData::SetDefaultValues()
{
    if (isFirstLoad) {
        //set values
        cameraSpeedModifier.X = 1; cameraSpeedModifier.Y = 1;

        //set bool to note that first load has occured
        isFirstLoad = false;

        //setup for level objects
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////

        //TUTORIAL
        levelObjectStateData.Add("tutorial_First_Gate", 0);
        levelObjectStateData.Add("tutorial_Ladder_Gate", 0);
        levelObjectStateData.Add("tutorial_Ramp_Gate", 0);
        levelObjectStateData.Add("brutach_Entry_FogGate", 0);
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////
    }
    else {

    }
}

void UGlobalTempData::PlayerDeathDataClear()
{
    player = nullptr;
    enemiesInScene.Empty();

    return;
}

void UGlobalTempData::LoadPlayerStateFromTemporaryData(UPlayerInventory* inventoryObjectToWrite)
{
    GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor::Red, FString::Printf(TEXT("Weapon Lists; left: %i, right: %i"), inventoryObjectToWrite->leftWeaponsEquipped.Num(), inventoryObjectToWrite->rightWeaponsEquipped.Num()));

    for (int i = 0; i < playerWeaponList.Num(); i++) {
        //create the weapon from the given class
        FActorSpawnParameters spawnParams;
        spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
        FTransform blankTransform = player->GetTransform();
        AUsableWeapon* spawnedWeapon = Cast<AUsableWeapon>(GetWorld()->SpawnActor<AActor>(playerWeaponList[i], blankTransform, spawnParams));

        //add it to weapon list
        inventoryObjectToWrite->weaponList.Add(spawnedWeapon);

        //turn off rendering and tick on spawned weapon to decrease resource use
        spawnedWeapon->DisableWeapon();

        if (spawnedWeapon != nullptr) {
            GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor::Red, FString::Printf(TEXT("WEAPON LOADED")));
        }
    }

    playerWeaponList.Empty();

    int selectIndex = 0;
    for (int i = 0; i < playerEquippedWeaponList.Num(); i++) {
        if (playerEquippedWeaponList[i] != nullptr) {
            for (int j = 0; j < inventoryObjectToWrite->weaponList.Num(); j++) {
                AUsableWeapon* objectToTest = inventoryObjectToWrite->weaponList[j];
                if (objectToTest->GetClass() == playerEquippedWeaponList[i] && !inventoryObjectToWrite->leftWeaponsEquipped.Contains(objectToTest) && !inventoryObjectToWrite->rightWeaponsEquipped.Contains(objectToTest)) {
                    if (i <= 2) {
                        inventoryObjectToWrite->leftWeaponsEquipped[i] = objectToTest;
                        //GEngine->AddOnScreenDebugMessage(-1,10.0f,FColor::Red, FString::Printf(TEXT("WEAPON %i selected for slot %i"), i, j));
                        break;
                    }
                    else {
                        inventoryObjectToWrite->rightWeaponsEquipped[i - 3] = objectToTest;
                        //GEngine->AddOnScreenDebugMessage(-1,10.0f,FColor::Red, FString::Printf(TEXT("WEAPON %i selected for slot %i"), i, j));
                        break;
                    }
                }
            }
        }
        else {
            if (i <= 2) {
                inventoryObjectToWrite->leftWeaponsEquipped[i] = nullptr;
            }
            else {
                inventoryObjectToWrite->rightWeaponsEquipped[i - 3] = nullptr;
            }
        }
    }

    //DEBUG
    for (int i = 0; i < inventoryObjectToWrite->leftWeaponsEquipped.Num(); i++) {
        if (inventoryObjectToWrite->leftWeaponsEquipped[i]) {
            GEngine->AddOnScreenDebugMessage(-1,10.0f,FColor::Red, FString::Printf(TEXT("LEFT WEAPON added in slot %i"), i));
        }
    }
    for (int i = 0; i < inventoryObjectToWrite->rightWeaponsEquipped.Num(); i++) {
        if (inventoryObjectToWrite->rightWeaponsEquipped[i]) {
            GEngine->AddOnScreenDebugMessage(-1,10.0f,FColor::Red, FString::Printf(TEXT("RIGHT WEAPON added in slot %i"), i));
        }
    }
    //DEBUG

    if (inventoryObjectToWrite->leftWeaponsEquipped[0] != nullptr) {
        inventoryObjectToWrite->leftWeaponsEquipped[0]->EnableWeapon();
    }
    if (inventoryObjectToWrite->rightWeaponsEquipped[0] != nullptr) {
        inventoryObjectToWrite->rightWeaponsEquipped[0]->EnableWeapon();
    }

    return;
}

void UGlobalTempData::WritePlayerStateToTemporaryData(UPlayerInventory* inventoryObjectToCopy)
{
    //clear necessary data
    playerWeaponList.Empty();
    playerEquippedWeaponList.Empty();
    
    //copy player weapon inventory to save data
    TArray<AUsableWeapon*> listToCopy = inventoryObjectToCopy->weaponList;
    for (int i = 0; i < listToCopy.Num(); i++) {
        playerWeaponList.Add(listToCopy[i]->GetClass());
    }

    //copy player equipment to save data
    for (int i = 0; i < inventoryObjectToCopy->leftWeaponsEquipped.Num(); i++) {
        if (inventoryObjectToCopy->leftWeaponsEquipped[i] != nullptr) {
            playerEquippedWeaponList.Add(inventoryObjectToCopy->leftWeaponsEquipped[i]->GetClass());
        }
        else {
            playerEquippedWeaponList.Add(nullptr);
        }
    }
    for (int i = 0; i < inventoryObjectToCopy->rightWeaponsEquipped.Num(); i++) {
        if (inventoryObjectToCopy->rightWeaponsEquipped[i] != nullptr) {
            playerEquippedWeaponList.Add(inventoryObjectToCopy->rightWeaponsEquipped[i]->GetClass());   
        }
        else {
            playerEquippedWeaponList.Add(nullptr);
        }
    }
}