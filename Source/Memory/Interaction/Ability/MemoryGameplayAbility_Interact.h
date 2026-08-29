// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Memory/AbilitySystem/Ability/MemoryGameplayAbility.h"
#include "Memory/Interaction/InteractionOption.h"//
#include "MemoryGameplayAbility_Interact.generated.h"

/**
 * 
 */
UCLASS()
class MEMORY_API UMemoryGameplayAbility_Interact : public UMemoryGameplayAbility
{
	GENERATED_BODY()

public:

	virtual void ExtraInputPressed(const FGameplayTag& ExtraInputTag) override;

protected:

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
		const FGameplayEventData* TriggerEventData) override;

	UFUNCTION(BlueprintCallable, Category = "GA_Interact")
	void UpdateInteractions(const TArray<FInteractionOption>& InteractiveOptions);

	UFUNCTION(BlueprintCallable, Category = "GA_Interact")
	void TriggerInteraction();

protected:

	UPROPERTY()
	TArray<FInteractionOption> Options;

	int32 SelectedIndex = 0;

	UPROPERTY(EditDefaultsOnly, Category = "GA_Interact|ScanParam")
	float InteractionScanRate = 0.1f;

	UPROPERTY(EditDefaultsOnly, Category = "GA_Interact|ScanParam")
	float InteractionScanRange = 500;
};