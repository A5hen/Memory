// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "MemoryAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class MEMORY_API UMemoryAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
	
public:

	virtual void InitAbilityActorInfo(AActor* InAvatarActor, AActor* InOwnerActor) override;

	void AbilityInputTagPressed(const FGameplayTag& InputTag);
	void AbilityInputTagReleased(const FGameplayTag& InputTag);

	void ProcessAbilityInput(float DeltaTime, bool bGamePaused);
	void ClearAbilityInput();

protected:

	void TryActivateAbilitiesOnSpawn();

	virtual void AbilitySpecInputPressed(FGameplayAbilitySpec& Spec) override;
	virtual void AbilitySpecInputReleased(FGameplayAbilitySpec& Spec) override;

protected:

	FGameplayTag InputTag_Pressed = FGameplayTag();

	TArray<FGameplayAbilitySpecHandle> InputPressedSpecHandles;

	TArray<FGameplayAbilitySpecHandle> InputReleasedSpecHandles;

	TArray<FGameplayAbilitySpecHandle> InputHeldSpecHandles;

	TArray<FGameplayAbilitySpecHandle> ExtraInputSpecHandles;
};