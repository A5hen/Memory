// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "InteractableActorSet.generated.h"

class AInteractableActor;

USTRUCT(BlueprintType)
struct FInteractableActorInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<AInteractableActor> InteractableActorClass;
};

/**
 * 
 */
UCLASS()
class MEMORY_API UInteractableActorSet : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:

	const FInteractableActorInfo* GetInteractableActorInfo(int32 ActorID) const;

protected:

	UPROPERTY(EditDefaultsOnly, Category = "InteractableActorInfomation")
	TMap<int32, FInteractableActorInfo>InteractableActorInfomation;
};