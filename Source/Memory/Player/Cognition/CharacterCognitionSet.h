// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"//
#include "CharacterCognitionSet.generated.h"

USTRUCT(BlueprintType)
struct FCognitoinLevel
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FText CognitionDesc;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FText EffectDesc;
};

USTRUCT(BlueprintType)
struct FBehaviorCognition
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FVector2D PositionOnGraph = FVector2D();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TMap<FGameplayTag, FText> SourceEventDesc;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TArray<FCognitoinLevel> CognitionLevels;
};

USTRUCT(BlueprintType)
struct FBehaviorCognitions
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FName, FBehaviorCognition> DescToCognition;
};

/**
 * 
 */
UCLASS()
class MEMORY_API UCharacterCognitionSet : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:

	const FBehaviorCognition* GetBehaviorCognition(const FGameplayTag& CharacterTag, const FName& BehaviorDesc) const;

protected:

	UPROPERTY(EditDefaultsOnly, Category = "CharacterCognitions")
	TMap<FGameplayTag, FBehaviorCognitions> CharacterBehaviorCognitions;
};