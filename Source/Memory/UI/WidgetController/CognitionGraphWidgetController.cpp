// Fill out your copyright notice in the Description page of Project Settings.


#include "CognitionGraphWidgetController.h"
#include "Memory/Player/MemoryPlayerState.h"//

void UCognitionGraphWidgetController::BroadcastInitialValues()
{
	if (GetMemoryPS())
	{
		const TMap<FGameplayTag, FGeneratedBehavior>& GeneratedCharacterBehaviors = MemoryPS->GetGeneratedCharacterBehaviors();
		GenerateCognitionMenu.Broadcast(GeneratedCharacterBehaviors);
	}
}

void UCognitionGraphWidgetController::BindCallBacksToDependencies()
{
	if (GetMemoryPS())
	{
		MemoryPS->OnCharacterBehaviorUpdated.AddLambda(
			[this](const FGameplayTag& CharacterTag, const FGeneratedBehavior& GeneratedBehavior, bool bNewCharacter)
			{
				UpdateCognitionGraph.Broadcast(CharacterTag, GeneratedBehavior, bNewCharacter);
			});
	}
}