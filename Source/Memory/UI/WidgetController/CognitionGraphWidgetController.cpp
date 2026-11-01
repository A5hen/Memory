// Fill out your copyright notice in the Description page of Project Settings.


#include "CognitionGraphWidgetController.h"
#include "Memory/Player/MemoryPlayerState.h"//

void UCognitionGraphWidgetController::BroadcastInitialValues()
{
	if (GetMemoryPS())
	{
		const TMap<FGameplayTag, FGeneratedBehavior>& GeneratedCharacterBehaviors = MemoryPS->GetGeneratedCharacterBehaviors();
		UpdateCognitionMenu.Broadcast(GeneratedCharacterBehaviors);
	}
}

void UCognitionGraphWidgetController::BindCallBacksToDependencies()
{
	if (GetMemoryPS())
	{
		MemoryPS->OnCharacterBehaviorsUpdated.AddLambda(
			[this](const TMap<FGameplayTag, FGeneratedBehavior>& GeneratedCharacterBehaviors)
			{
				UpdateCognitionMenu.Broadcast(GeneratedCharacterBehaviors);
			});
	}
}

const FGeneratedBehaviorCognition* UCognitionGraphWidgetController::GetGeneratedBehaviorCognition(const FGameplayTag& CharacterTag, const FName& BehaviorDesc)
{
	if (GetMemoryPS())
	{
		if (const FGeneratedBehavior* GeneratedBehavior = MemoryPS->GetGeneratedBehavior(CharacterTag))
		{
			return GeneratedBehavior->DescToCognition.Find(BehaviorDesc);
		}
	}

	return nullptr;
}