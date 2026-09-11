// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameplayTagContainer.h"//
#include "MemoryEventLibrary.generated.h"

class UMemoryEventManager;

/**
 * 
 */
UCLASS()
class MEMORY_API UMemoryEventLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "MemoryEventLibrary", meta = (DefaultToSelf = "WorldContextObject"))
	static void FinishEventAsyncAction(const UObject* WorldContextObject, EActionType ActionType, FGameplayTag ActorTag);

	UFUNCTION(BlueprintCallable, Category = "MemoryEventLibrary", meta = (DefaultToSelf = "WorldContextObject"))
	static void SendDialogueResult(const UObject* WorldContextObject, FGameplayTag ActorTag, int32 SentenceIndex, FText Result);
};