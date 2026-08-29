// Fill out your copyright notice in the Description page of Project Settings.


#include "MemoryEventLibrary.h"
#include "Kismet/GameplayStatics.h"//
#include "Memory/GameMode/MemoryEventManager.h"//

void UMemoryEventLibrary::FinishEventAsyncAction(const UObject* WorldContextObject, EActionType ActionType, FGameplayTag ActorTag)
{
	if(UWorld* World = WorldContextObject->GetWorld())
	{
		UMemoryEventManager* EventManager = World->GetSubsystem<UMemoryEventManager>();
		if (EventManager)
		{
			EventManager->FinishEventAsyncAction(ActorTag, ActionType);
		}
	}
}

void UMemoryEventLibrary::SendDialogueSelectionResult(const UObject* WorldContextObject, int32 SentenceIndex, int32 Result)
{
	if (UWorld* World = WorldContextObject->GetWorld())
	{
		UMemoryEventManager* EventManager = World->GetSubsystem<UMemoryEventManager>();
		if (EventManager)
		{
			EventManager->SendDialogueSelectionResult(SentenceIndex, Result);
		}
	}
}