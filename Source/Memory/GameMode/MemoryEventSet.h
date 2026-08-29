// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"//
#include "MemoryEventSet.generated.h"

class UMemoryEventDefinition;

UENUM(BlueprintType)
enum class EPreEventConnectType: uint8
{
	TopToBottom,
	TopToLeft,
	TopToRight,
	BottomToTop,
	BottomToLeft,
	BottomToRight,
	LeftToTop,
	LeftToBottom,
	LeftToRight,
	RightToTop,
	RightToBottom,
	RightToLeft,
};

USTRUCT(BlueprintType)
struct FMemoryEventInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<UMemoryEventDefinition> EventDefinition;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FVector2D PositionOnGraph;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float Size = 500.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FGameplayTagContainer PreEventTags;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TMap<FGameplayTag, EPreEventConnectType> PreEventConnectRule;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FGameplayTagContainer PostEventTags;
};

/**
 * 
 */
UCLASS()
class MEMORY_API UMemoryEventSet : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:

	const FMemoryEventInfo* GetEventInfoByEventTag(const FGameplayTag& EventTag) const;

	void GenerateEventConnectInfo(EPreEventConnectType PreEventConnectType,
		const FVector2D& Start, const FVector2D& End, float StartSize, float EndSize,
		FVector2D& OutStart, FVector2D& OutEnd);
	
protected:

	UPROPERTY(EditDefaultsOnly, Category = "EventInfomation")
	TMap<FGameplayTag, FMemoryEventInfo> EventInfomation;
};