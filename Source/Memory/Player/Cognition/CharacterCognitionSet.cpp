// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterCognitionSet.h"

const FBehaviorCognition* UCharacterCognitionSet::GetBehaviorCognition(const FGameplayTag& CharacterTag, const FName& BehaviorDesc) const
{
	if (const FBehaviorCognitions* BehaviorCognitions = CharacterBehaviorCognitions.Find(CharacterTag))
	{
		return BehaviorCognitions->DescToCognition.Find(BehaviorDesc);
	}

	return nullptr;
}