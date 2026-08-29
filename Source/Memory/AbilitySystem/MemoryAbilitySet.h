// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"//
#include "MemoryAbilitySet.generated.h"

class AbilitySystemComponent;
class UMemoryGameplayAbility;

USTRUCT(BlueprintType)
struct FMemoryAbilityInfo
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<UMemoryGameplayAbility> Ability;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 AbilityLevel;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FGameplayTag AbilityTag;
};

/**
 * 
 */
UCLASS(BlueprintType)
class MEMORY_API UMemoryAbilitySet : public UDataAsset
{
	GENERATED_BODY()

public:

	const FMemoryAbilityInfo* GetAbilityInfo(const FGameplayTag& AbilityTag) const;

protected:

	UPROPERTY(EditDefaultsOnly, Category = "AbilityInfomation")
	TArray<FMemoryAbilityInfo> AbilityInfomation;
};