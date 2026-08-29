// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Memory/UI/GraphNodeWidget.h"
#include "GameplayTagContainer.h"//
#include "EventGraphNode.generated.h"

class UCanvasPanel;

class UEGLN_CharacterBehavior;
class UEGLN_SelfAwareness;

struct FExperiencedEventInfo;

/**
 * 
 */
UCLASS()
class MEMORY_API UEventGraphNode : public UGraphNodeWidget
{
	GENERATED_BODY()

public:

	void UpdateLeafNode(const FGameplayTag& EventTag, const FExperiencedEventInfo& ExperiencedEventInfo);

protected:

	void UpdateLeafNode_CharacterBehavior(const FGameplayTag& EventTag, const FExperiencedEventInfo& ExperiencedEventInfo);
	void UpdateLeafNode_SelfAwareness(const FGameplayTag& EventTag, const FExperiencedEventInfo& ExperiencedEventInfo);
	
protected:

	UPROPERTY(meta = (BindWidget))
	UCanvasPanel* CanvasPanel_Root;

	UPROPERTY(EditDefaultsOnly, Category = "LeafNode")
	TSubclassOf<UEGLN_CharacterBehavior> LeafNode_CharacterBehaviorClass;

	UPROPERTY()
	TObjectPtr<UEGLN_CharacterBehavior> LeafNode_CharacterBehavior;

	UPROPERTY(EditDefaultsOnly, Category = "LeafNode")
	TSubclassOf<UEGLN_SelfAwareness> LeafNode_SelfAwarenessClass;

	UPROPERTY()
	TObjectPtr<UEGLN_SelfAwareness> LeafNode_SelfAwareness;
};