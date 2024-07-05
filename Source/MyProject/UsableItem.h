// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/Texture.h"
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
		UTexture2D* itemImage;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FText itemName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FText ItemDescription;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FText fullItemDescription;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool isConsumable;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FString itemType;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
