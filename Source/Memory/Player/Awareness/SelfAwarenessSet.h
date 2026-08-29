// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"//
#include "SelfAwarenessSet.generated.h"

USTRUCT(BlueprintType)
struct FEffectOnBehaviorCognition
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TMap<FName, int32> NewCognitionLevel;
};

USTRUCT(BlueprintType)
struct FAwarenessInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TMap<FGameplayTag, FEffectOnBehaviorCognition> EffectOnCharacterBehaviorCognition;
};

/**
 * 
 */
UCLASS()
class MEMORY_API USelfAwarenessSet : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:

	const FAwarenessInfo* GetAwarenessInfo_Single(const FGameplayTag& AwarenessTag) const;

	const FGameplayTagContainer* GetTagContainerKey(int32 Index) const;

    const FAwarenessInfo* GetAwarenessInfo_Group(int32 Index) const;

protected:

	UPROPERTY(EditDefaultsOnly, Category = "AwarenessInfomation_Single")
	TMap<FGameplayTag, FAwarenessInfo>AwarenessInfomation_Single;

    UPROPERTY(EditDefaultsOnly, Category = "TagContainerKey")
    TMap<int32, FGameplayTagContainer> IndexToTagContainerKey;

	UPROPERTY(EditDefaultsOnly, Category = "AwarenessInfomation_Group")
	TMap<int32, FAwarenessInfo>AwarenessInfomation_Group;
};