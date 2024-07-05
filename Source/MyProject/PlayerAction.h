// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerControllerV2.h"
#include "PlayerAction.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class MYPROJECT_API UPlayerAction : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerAction();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void EnterState();
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		APlayerControllerV2* player;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		USkeletalMeshComponent* playerSkeletalMesh;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float staminaCost;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float moveScalar = 0;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float mouseScalar = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool canBufferFromDefault;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool canRegainStamina;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool flipAnimations;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool forceUncrouch = true;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
