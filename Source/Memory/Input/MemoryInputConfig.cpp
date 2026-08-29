// Fill out your copyright notice in the Description page of Project Settings.


#include "MemoryInputConfig.h"

UInputAction* UMemoryInputConfig::FindInputActionByTag(const FGameplayTag& InputTag)
{
	for (const FMemoryInputAction& Action : MemoryInputActions)
	{
		if (Action.InputTag.MatchesTagExact(InputTag))
		{
			return Action.InputAction;
		}
	}

	return nullptr;
}