// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"//
#include "MemoryInputConfig.generated.h"

class UInputAction;

USTRUCT(BlueprintType)
struct FMemoryInputAction
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	UInputAction* InputAction = nullptr;

	UPROPERTY(EditDefaultsOnly)
	FGameplayTag InputTag = FGameplayTag();
};

/**
 * 
 */
UCLASS()
class MEMORY_API UMemoryInputConfig : public UDataAsset
{
	GENERATED_BODY()

public:

	UInputAction* FindInputActionByTag(const FGameplayTag& InputTag);

	UPROPERTY(EditDefaultsOnly)
	TArray<FMemoryInputAction> MemoryInputActions;
};