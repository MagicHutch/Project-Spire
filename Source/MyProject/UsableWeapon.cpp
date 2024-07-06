// Fill out your copyright notice in the Description page of Project Settings.


#include "UsableWeapon.h"

AUsableWeapon::AUsableWeapon()
{
    itemType = "WEAPON";
}

void AUsableWeapon::EnableWeapon()
{
    SetActorHiddenInGame(false);
    SetActorTickEnabled(true);

    return;
}

void AUsableWeapon::DisableWeapon()
{
    SetActorHiddenInGame(true);
    SetActorTickEnabled(false);

    return;
}