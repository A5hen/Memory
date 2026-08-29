// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "GameplayTagContainer.h"//
#include "Memory/Memory.h"//
#include "MemoryEventManager.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnEventStarted);//TO DO

class UMemoryEventDefinition;
class UMemoryEventSet;

/**
 * 
 */
UCLASS(BlueprintType)
class MEMORY_API UMemoryEventManager : public UWorldSubsystem
{
	GENERATED_BODY()

public:

	UMemoryEventManager();

	void SetOutterWorldContext(UWorld* OutterWorldContext);
	void SetPlayerController(APlayerController* InPlayerController);

	void ConfirmStartEventCondition(const FString& ConditionKey);

	/*EventDefinition*/
	void FinishEventAsyncAction(const FGameplayTag& ActorTag, EActionType ActionType);

	UFUNCTION(BlueprintCallable, Category = "EventManager")
	void SendDialogueSelectionResult(int32 SentenceIndex, int32 Result);
	/*EventDefinition*/

protected:

	void StartNextEvent();
	void OnEventStepFinished(int32 StepIndex);

	UMemoryEventSet* GetMemoryEventSet();

protected:

	UPROPERTY()
	TObjectPtr<UMemoryEventSet> EventSet;

	UPROPERTY()
	TObjectPtr<UMemoryEventDefinition> OngoingEventDefinition;

	int32 OngoingStepIndex = 0;

	TMap<FString, bool>StartEventConditions;

	UPROPERTY()
	TObjectPtr<UWorld> WorldContext;

	UPROPERTY()
	TObjectPtr<APlayerController> PlayerController;
};