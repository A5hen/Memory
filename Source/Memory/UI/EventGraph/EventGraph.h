// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Memory/UI/GraphWidget.h"
#include "GameplayTagContainer.h"//
#include "EventGraph.generated.h"

class UEventGraphNode;

class UMemoryWidgetController;

struct FExperiencedEventInfo;
struct FExperiencedEventInfomation;

class UMemoryEventSet;

/**
 * 
 */
UCLASS()
class MEMORY_API UEventGraph : public UGraphWidget
{
	GENERATED_BODY()

public:

	virtual void SetWidgetController(UMemoryWidgetController* InWidgetController) override;
	virtual void ClearGraph() override;
	virtual void UnbindCallBacks() override;

protected:

	void UpdateEventGraph(const FExperiencedEventInfomation& ExperiencedEventInfomation);
	void UpdateEventGraphNode(const FGameplayTag& EventTag, const FExperiencedEventInfo& ExperiencedEventInfo, bool bGenerated = false, const FVector2D& PositionOnGraph = FVector2D());

	UMemoryEventSet* GetEventSet();

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Node")
	TSubclassOf<UEventGraphNode> EventGraphNodeClass;

	UPROPERTY()
	TMap<FGameplayTag, TObjectPtr<UEventGraphNode>> GeneratedEventGraphNodes;

	UPROPERTY()
	TObjectPtr<UMemoryEventSet> EventSet;
};