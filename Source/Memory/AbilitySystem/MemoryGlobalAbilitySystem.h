// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "GamePlayTagContainer.h"//
#include "MemoryGlobalAbilitySystem.generated.h"

class UMemoryAbilitySet;
class UMemoryAbilitySystemComponent;

/**
 * 
 */
UCLASS()
class MEMORY_API UMemoryGlobalAbilitySystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:

	void RegisterASC(UMemoryAbilitySystemComponent* ASC);

	void GrantAbilitiesToAbilitySystem(const FGameplayTagContainer& AbilityTags);

protected:

	UPROPERTY()
	TObjectPtr<UMemoryAbilitySet> AbilitySet = nullptr;

	UPROPERTY()
	TObjectPtr<UMemoryAbilitySystemComponent> MemoryASC = nullptr;
};