// Fill out your copyright notice in the Description page of Project Settings.


#include "EventAsyncAction.h"
#include "Kismet/GameplayStatics.h"//
#include "Memory/GameMode/MemoryEventDefinition.h"//

UEventAsyncAction* UEventAsyncAction::EventAsyncAction(
	UMemoryEventDefinition* InEventDefinition,
	FName InActionName, EActionType InActionType, FGameplayTag InActorTag, const TArray<FName>& InStartCondition)
{
	check(InEventDefinition);

	UEventAsyncAction* AsyncAction = NewObject<UEventAsyncAction>();
	AsyncAction->OwnerEventDefinition = InEventDefinition;
	AsyncAction->ActionName = InActionName;
	AsyncAction->ActionType = InActionType;
	AsyncAction->ActorTag = InActorTag;
	AsyncAction->StartCondition = InStartCondition;

	return AsyncAction;
}

void UEventAsyncAction::Activate()
{
	if (OwnerEventDefinition)
	{
		OwnerEventDefinition->RegisterEventAsyncAction(this);
	}
	else
	{
		Destory();
	}
}

void UEventAsyncAction::Destory()
{
	if (ListenDialogueResult)
	{
		ListenDialogueResult->Destory();
	}

	SetReadyToDestroy();
	MarkAsGarbage();
}

void UEventAsyncAction::Start()
{
	OnActionStarted.Broadcast();
}

void UEventAsyncAction::Finish()
{
	bFinished = true;

	OnActionFinished.Broadcast();
}

void UEventAsyncAction::ActivateNextAsyncAction()
{
	NextAsyncAction.Broadcast();
}

void UEventAsyncAction::ListenDialogue(UListenDialogueResult* InListenDialogueResult)
{
	ListenDialogueResult = InListenDialogueResult;
}

void UEventAsyncAction::SendDialogueResult(int32 SentenceIndex, FText Result)
{
	if (ListenDialogueResult)
	{
		ListenDialogueResult->OnResultReceived.Broadcast(SentenceIndex, Result);
	}
}

bool UEventAsyncAction::CheckStartCondition(const TArray<FName>& InFinishedActions) const
{
	//return InFinishedActions.Contains(StartCondition);
	return true;
}

//
//
//

UListenDialogueResult* UListenDialogueResult::ListenDialogueResult(UEventAsyncAction* InAsyncAction)
{
	check(InAsyncAction);

	UListenDialogueResult* AsyncAction = NewObject<UListenDialogueResult>();
	InAsyncAction->ListenDialogue(AsyncAction);

	return AsyncAction;
}

void UListenDialogueResult::Activate()
{

}

void UListenDialogueResult::Destory()
{
	SetReadyToDestroy();
	MarkAsGarbage();
}