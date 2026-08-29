// Fill out your copyright notice in the Description page of Project Settings.


#include "MemoryAbilitySet.h"
#include "Memory/AbilitySystem/MemoryAbilitySystemComponent.h"//
#include "Memory/AbilitySystem/Ability/MemoryGameplayAbility.h"//

const FMemoryAbilityInfo* UMemoryAbilitySet::GetAbilityInfo(const FGameplayTag& AbilityTag) const
{
	for (const FMemoryAbilityInfo& AbilityInfo : AbilityInfomation)
	{
		if (AbilityInfo.AbilityTag.MatchesTagExact(AbilityTag))
		{
			return &AbilityInfo;
		}
	}

	return nullptr;
}