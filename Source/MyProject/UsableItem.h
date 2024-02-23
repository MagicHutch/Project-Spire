// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Styling/SlateBrush.h"
#include "GameFramework/Actor.h"
#include "UsableItem.generated.h"

UCLASS()
class MYPROJECT_API AUsableItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUsableItem();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UTexture* itemImage;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FText itemName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FText ItemDescription;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool isConsumable;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
