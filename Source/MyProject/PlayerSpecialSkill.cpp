// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerSpecialSkill.h"

APlayerSpecialSkill::APlayerSpecialSkill()
{
    itemType = "SKILL";
}

void APlayerSpecialSkill::ToggleObjectTick(bool canTick)
{
    SetActorTickEnabled(canTick);
}

void APlayerSpecialSkill::ToggleObjectVisibility(bool isVisible)
{
    if (isVisible) {
        SetActorHiddenInGame(false);
    }
    else {
        SetActorHiddenInGame(true);
    }
}

void APlayerSpecialSkill::ToggleIsEquipped(bool isEquipped)
{
    if (isEquipped) {
        ToggleObjectTick(tickEnabledWhenEquipped);
        ToggleObjectVisibility(isVisibleWhenEquipped);
    }

    else {
        ToggleObjectTick(tickEnabledOnSpawn);
        ToggleObjectVisibility(isVisibleOnSpawn);
    }
}