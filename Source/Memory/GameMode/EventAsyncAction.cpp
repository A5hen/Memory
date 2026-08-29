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

bool UEventAsyncAction::CheckStartCondition(const TArray<FName>& InFinishedActions) const
{
	//return InFinishedActions.Contains(StartCondition);
	return true;
}

//
//
//

UListenDialogueSelectionResult* UListenDialogueSelectionResult::ListenDialogueSelectionResult(UMemoryEventDefinition* InEventDefinition)
{
	check(InEventDefinition);

	UListenDialogueSelectionResult* AsyncAction = NewObject<UListenDialogueSelectionResult>();
	AsyncAction->OwnerEventDefinition = InEventDefinition;

	return AsyncAction;
}

void UListenDialogueSelectionResult::Activate()
{
	if (OwnerEventDefinition)
	{
		OwnerEventDefinition->RegisterDialogueSelectionListener(this);
	}
	else
	{
		Destory();
	}
}

void UListenDialogueSelectionResult::Destory()
{
	SetReadyToDestroy();
	MarkAsGarbage();
}