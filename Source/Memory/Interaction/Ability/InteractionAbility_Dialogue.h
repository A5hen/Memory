// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Memory/AbilitySystem/Ability/MemoryGameplayAbility.h"
#include "Memory/Interaction/InteractableTarget.h"//
#include "InteractionAbility_Dialogue.generated.h"

struct FDialogueContent;

class IInteractableTarget;

/**
 * 
 */
UCLASS()
class MEMORY_API UInteractionAbility_Dialogue : public UMemoryGameplayAbility
{
	GENERATED_BODY()

protected:

	UFUNCTION(BlueprintCallable, Category = "GA_Dialogue")
	bool SetParams(const FGameplayEventData& EventData);

	UFUNCTION(BlueprintCallable, Category = "GA_Dialogue")
	bool UpdateDialogueContent(FText& Sentence, TArray<FText>& Options);

	UFUNCTION(BlueprintCallable, Category = "GA_Dialogue")
	void ReceiveSelectionResult(const FText& Option);

	UFUNCTION(BlueprintCallable, Category = "GA_Dialogue")
	void InterruptDialogue();

protected:

	UPROPERTY(BlueprintReadOnly, Category = "GA_Dialogue")
	FGameplayTag ActorTag;

	UPROPERTY()
	TScriptInterface<IInteractableTarget> InteractableTarget;

	int32 CurrentBranchIndex = 0;

	int32 NextSentenceIndex = 0;

	FDialogueContent DialogueContent;

	bool bInterrupted = false;
};