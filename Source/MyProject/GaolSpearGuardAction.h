// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GaolSpearGuardAction.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable )
class MYPROJECT_API UGaolSpearGuardAction : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGaolSpearGuardAction();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void UseAction();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		USkeletalMeshComponent* parentSkeletalMesh;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float staminaCost;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
