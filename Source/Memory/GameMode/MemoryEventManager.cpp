// Fill out your copyright notice in the Description page of Project Settings.


#include "MemoryEventManager.h"
#include "Memory/MemoryAssetManager.h"//
#include "Memory/GameMode/MemoryEventDefinition.h"//
#include "Memory/GameMode/MemoryEventSet.h"//
#include "Memory/GameInstance/MemoryGameInstance.h"//
#include "Memory/MemoryGameplayTag.h"//

UMemoryEventManager::UMemoryEventManager()
{
	StartEventConditions.Emplace("SpawnPoint", false);
	StartEventConditions.Emplace("Player", false);
}

void UMemoryEventManager::SetOutterWorldContext(UWorld* OutterWorldContext)
{
	WorldContext = OutterWorldContext;
}

void UMemoryEventManager::SetPlayerController(APlayerController* InPlayerController)
{
	PlayerController = InPlayerController;
}

void UMemoryEventManager::ConfirmStartEventCondition(const FString& ConditionKey)
{
	if(StartEventConditions.Find(ConditionKey))
	{
		StartEventConditions[ConditionKey] = true;
	}

	int32 Count = 0;

	for(const auto& Condition : StartEventConditions)
	{	
		if (Condition.Value)
		{
			++Count;
		}

		if (Count == StartEventConditions.Num())
		{
			StartNextEvent();
		}
	}
}

void UMemoryEventManager::FinishEventAsyncAction(const FGameplayTag& ActorTag, EActionType ActionType)
{
	if(OngoingEventDefinition)
	{
		OngoingEventDefinition->FinishEventAsyncAction(ActorTag, ActionType);
	}
}

void UMemoryEventManager::SendDialogueSelectionResult(int32 SentenceIndex, int32 Result)
{
	if (OngoingEventDefinition)
	{
		OngoingEventDefinition->SendDialogueSelectionResult(SentenceIndex, Result);
	}
}

UMemoryEventSet* UMemoryEventManager::GetMemoryEventSet()
{
	if (EventSet == nullptr && GetWorld())
	{
		UMemoryGameInstance* MemoryGI = GetWorld()->GetGameInstance<UMemoryGameInstance>();
		EventSet = MemoryGI->GetMemoryEventSet();
	}

	return EventSet;
}

void UMemoryEventManager::StartNextEvent()
{
	if (!GetMemoryEventSet() || !WorldContext || !PlayerController)return;

	const FMemoryGameplayTags& GameplayTags = FMemoryGameplayTags::Get();

	const FMemoryEventInfo* EventInfo = EventSet->GetEventInfoByEventTag(GameplayTags.Event_Test);
	if (!EventInfo)return;

	if (OngoingEventDefinition = NewObject<UMemoryEventDefinition>(this, EventInfo->EventDefinition))
	{
		OngoingEventDefinition->SetEventTag(GameplayTags.Event_Test);
		OngoingEventDefinition->SetOutterWorldContext(WorldContext);
		OngoingEventDefinition->SetPlayerController(PlayerController);

		OngoingEventDefinition->OnEventStepFinished.AddUObject(this, &UMemoryEventManager::OnEventStepFinished);

		OngoingEventDefinition->SceneSetup();

		OngoingEventDefinition->StartEventStep(OngoingStepIndex);
	}
}

void UMemoryEventManager::OnEventStepFinished(int32 StepIndex)
{
	int32 StepNum = OngoingEventDefinition->GetEventStepNum();
	if (StepNum > 0 && StepIndex < StepNum - 1)
	{
		++OngoingStepIndex;
		OngoingEventDefinition->StartEventStep(OngoingStepIndex);
	}
	else
	{
		//Find Next EventTag
		//StartNextEvent();
	}
}