// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableObject.generated.h"

UCLASS()
class MYPROJECT_API AInteractableObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractableObject();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void Interact();
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void HideTriggersOnStartup();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool showTriggersInGame = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FString levelObjectID;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int levelObjectState;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FText interactPrompt;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
