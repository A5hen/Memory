// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"//
#include "SelfAwarenessSet.generated.h"

USTRUCT(BlueprintType)
struct FBehaviorCognitionEffect
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
	TMap<FGameplayTag, FBehaviorCognitionEffect> CharacterBehaviorCognitionEffects;
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

	const FGameplayTagContainer* GetSelfAwarenessGroup(FName GroupName) const;

    const FAwarenessInfo* GetAwarenessInfo_Group(FName GroupName) const;

protected:

	UPROPERTY(EditDefaultsOnly, Category = "AwarenessInfomation_Single")
	TMap<FGameplayTag, FAwarenessInfo>AwarenessInfomation_Single;

    UPROPERTY(EditDefaultsOnly, Category = "TagContainerKey")
    TMap<FName, FGameplayTagContainer> SelfAwarenessGroup;

	UPROPERTY(EditDefaultsOnly, Category = "AwarenessInfomation_Group")
	TMap<FName, FAwarenessInfo>AwarenessInfomation_Group;
};