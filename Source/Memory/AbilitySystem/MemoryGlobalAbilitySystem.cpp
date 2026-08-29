// Fill out your copyright notice in the Description page of Project Settings.


#include "MemoryGlobalAbilitySystem.h"
#include "Memory/MemoryAssetManager.h"//
#include "Memory/AbilitySystem/MemoryAbilitySystemComponent.h"//
#include "Memory/AbilitySystem/MemoryAbilitySet.h"//
#include "Memory/AbilitySystem/Ability/MemoryGameplayAbility.h"//

void UMemoryGlobalAbilitySystem::RegisterASC(UMemoryAbilitySystemComponent* ASC)
{
	MemoryASC = ASC;
}

void UMemoryGlobalAbilitySystem::GrantAbilitiesToAbilitySystem(const FGameplayTagContainer& AbilityTags)
{
	check(MemoryASC);

	if (AbilitySet == nullptr)
	{
		FPrimaryAssetId AbilitySetId = FPrimaryAssetId(FName("MemoryAbilitySet"), FName("DA_AbilitySet"));
		UMemoryAssetManager& AssetManager = UMemoryAssetManager::Get();
		FSoftObjectPath AssetPath = AssetManager.GetPrimaryAssetPath(AbilitySetId);
		AbilitySet = Cast<UMemoryAbilitySet>(AssetPath.TryLoad());
		check(AbilitySet);
	}

	for (const FGameplayTag& AbilityTag : AbilityTags)
	{
		if (const FMemoryAbilityInfo* AbilityToGrant = AbilitySet->GetAbilityInfo(AbilityTag))
		{
			if (!IsValid(AbilityToGrant->Ability))
			{
				continue;
			}

			FGameplayAbilitySpec AbilitySpec(AbilityToGrant->Ability, AbilityToGrant->AbilityLevel);
			AbilitySpec.DynamicAbilityTags.AddTag(AbilityToGrant->AbilityTag);

			FGameplayAbilitySpecHandle AbilitySpecHandle = MemoryASC->GiveAbility(AbilitySpec);
		}
	}
}