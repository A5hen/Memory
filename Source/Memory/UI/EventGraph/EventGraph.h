// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Memory/UI/GraphWidget.h"
#include "Memory/MemoryType.h"//
#include "GameplayTagContainer.h"//
#include "EventGraph.generated.h"

class UEventGraphNode;

struct FExperiencedEventInfo;

class UMemoryEventSet;

/**
 * 
 */
UCLASS()
class MEMORY_API UEventGraph : public UGraphWidget
{
	GENERATED_BODY()

public:

	virtual void ClearGraph() override;

	bool CheckEvent(const FGameplayTag& EventTag) const;
	FVector2D JumpToEventGraphNode(const FGameplayTag& EventTag);

	void UpdateEventGraph(const FExperiencedEventInfomation& ExperiencedEventInfomation);

protected:

	void UpdateEventGraphNode(const FGameplayTag& EventTag, const FExperiencedEventInfo& ExperiencedEventInfo, const FVector2D& PositionOnGraph = FVector2D());

	UMemoryEventSet* GetEventSet();

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Node")
	TSubclassOf<UEventGraphNode> EventGraphNodeClass;

	UPROPERTY()
	TMap<FGameplayTag, TObjectPtr<UEventGraphNode>> GeneratedEventGraphNodes;

	UPROPERTY()
	TObjectPtr<UMemoryEventSet> EventSet;
};