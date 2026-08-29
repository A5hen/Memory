// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GameplayTagContainer.h"//
#include "MemoryGameplayAbility.generated.h"

UENUM(BlueprintType)
enum class EMemoryAbilityActivationPolicy : uint8
{
	OnInputTriggered,

	WhileInputActive,

	OnSpawn
};

/**
 * 
 */
UCLASS()
class MEMORY_API UMemoryGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:

	virtual void ExtraInputPressed(const FGameplayTag& ExtraInputTag);

	EMemoryAbilityActivationPolicy GetActivationPolicy() const { return ActivationPolicy; }
	const FGameplayTagContainer& GetExtraInputTags() const { return ExtraInputTags; }
	
	void TryActivateAbilityOnSpawn(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) const;

protected:

	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	virtual void OnRemoveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AbilityActivationPolicy")
	EMemoryAbilityActivationPolicy ActivationPolicy = EMemoryAbilityActivationPolicy::OnInputTriggered;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ExtraInput")
	FGameplayTagContainer ExtraInputTags = FGameplayTagContainer();
};