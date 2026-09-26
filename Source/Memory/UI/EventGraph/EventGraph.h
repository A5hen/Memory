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

	void UpdateEventGraph(const FExperiencedEventInfomation& ExperiencedEventInfomation);

	EEventStage GetEventStage() const { return EventStage; }
	void SetEventStage(EEventStage InEventStage) { EventStage = InEventStage; }

protected:

	void UpdateEventGraphNode(const FGameplayTag& EventTag, const FExperiencedEventInfo& ExperiencedEventInfo, bool bGenerated = false, const FVector2D& PositionOnGraph = FVector2D());

	UMemoryEventSet* GetEventSet();

protected:

	EEventStage EventStage;

	UPROPERTY(EditDefaultsOnly, Category = "Node")
	TSubclassOf<UEventGraphNode> EventGraphNodeClass;

	UPROPERTY()
	TMap<FGameplayTag, TObjectPtr<UEventGraphNode>> GeneratedEventGraphNodes;

	UPROPERTY()
	TObjectPtr<UMemoryEventSet> EventSet;
};