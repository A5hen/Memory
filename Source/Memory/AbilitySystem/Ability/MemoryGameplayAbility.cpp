// Fill out your copyright notice in the Description page of Project Settings.


#include "MemoryGameplayAbility.h"
#include "Memory/AbilitySystem/MemoryAbilitySystemComponent.h"//

void UMemoryGameplayAbility::ExtraInputPressed(const FGameplayTag& ExtraInputTag)
{
}

void UMemoryGameplayAbility::TryActivateAbilityOnSpawn(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) const
{
	if (ActorInfo && !Spec.IsActive() && ActivationPolicy == EMemoryAbilityActivationPolicy::OnSpawn)
	{
		UAbilitySystemComponent* ASC = ActorInfo->AbilitySystemComponent.Get();
	
		if (ASC)ASC->TryActivateAbility(Spec.Handle);
	}
}

void UMemoryGameplayAbility::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);

	TryActivateAbilityOnSpawn(ActorInfo, Spec);
}

void UMemoryGameplayAbility::OnRemoveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnRemoveAbility(ActorInfo, Spec);
}