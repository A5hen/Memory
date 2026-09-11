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

void UMemoryEventLibrary::SendDialogueResult(const UObject* WorldContextObject, FGameplayTag ActorTag, int32 SentenceIndex, FText Result)
{
	if (UWorld* World = WorldContextObject->GetWorld())
	{
		UMemoryEventManager* EventManager = World->GetSubsystem<UMemoryEventManager>();
		if (EventManager)
		{
			EventManager->SendDialogueResult(ActorTag, SentenceIndex, Result);
		}
	}
}