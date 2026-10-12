// Fill out your copyright notice in the Description page of Project Settings.


#include "EventGraph.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"//
#include "Blueprint/WidgetLayoutLibrary.h"//
#include "Memory/GameInstance/MemoryGameInstance.h"//
#include "Memory/GameMode/MemoryEventSet.h"//
#include "Memory/Player/MemoryPlayerState.h"//
#include "Memory/UI/EventGraph/EventGraphNode.h"//
#include "Memory/UI/CurveWidget.h"//

void UEventGraph::ClearGraph()
{
	for (auto& Pair : GeneratedEventGraphNodes)
	{
		if (Pair.Value)
		{
			Pair.Value->RemoveFromParent();
		}
	}

	GeneratedEventGraphNodes.Empty();

	Super::ClearGraph();
}

bool UEventGraph::CheckEventStage(const FGameplayTag& EventTag) const
{
	return GeneratedEventGraphNodes.Contains(EventTag);
}

FVector2D UEventGraph::JumptoEventGraphNode(const FGameplayTag& EventTag)
{
	if (UEventGraphNode* TargetNode = GeneratedEventGraphNodes.FindRef(EventTag).Get())
	{
		UCanvasPanelSlot* CanvasPanelSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(TargetNode);
		return CanvasPanelSlot->GetPosition();
	}

	return FVector2D();
}

void UEventGraph::UpdateEventGraph(const FExperiencedEventInfomation& ExperiencedEventInfomation)
{
	if (!GetEventSet())return;

	TArray<FGameplayTag> KeyArray;
	ExperiencedEventInfomation.TagToInfo.GenerateKeyArray(KeyArray);

	FGameplayTagContainer ExperiencedEvents;
	ExperiencedEvents.AppendTags(FGameplayTagContainer::CreateFromArray(KeyArray));

	for (const auto& Pair : ExperiencedEventInfomation.TagToInfo)
	{
		if(const FMemoryEventInfo* EventInfo = EventSet->GetEventInfoByEventTag(Pair.Key))
		{
			TArray<FVector2D> RelativePositionsToConnect;
			TMap<FVector2D, TArray<FVector2D>> PositionsToConnect;

			UpdateEventGraphNode(Pair.Key, Pair.Value, GeneratedEventGraphNodes.Contains(Pair.Key), EventInfo->PositionOnGraph);
			
			for(const auto& RelativePositionPair : Pair.Value.RelativePositions)
			{
				RelativePositionsToConnect.Add(RelativePositionPair.Value);
			}

			const FGameplayTagContainer& ExperiencedPreEvents = ExperiencedEvents.FilterExact(EventInfo->PreEventTags);
			for (const FGameplayTag& PreEventTag : ExperiencedPreEvents)
			{
				if(const FMemoryEventInfo* PreEventInfo = EventSet->GetEventInfoByEventTag(PreEventTag))
				{
					if (const EPreEventConnectType* PreEventConnectType = EventInfo->PreEventConnectRule.Find(PreEventTag))
					{
						FVector2D Start;
						FVector2D End;

						EventSet->GenerateEventConnectInfo(*PreEventConnectType,
							EventInfo->PositionOnGraph, PreEventInfo->PositionOnGraph, EventInfo->Size, PreEventInfo->Size, Start, End);

						TArray<FVector2D>& Array_End = PositionsToConnect.FindOrAdd(Start);
						Array_End.Add(End);
					}
				}
			}

			CurveWidget->UpdateCurveSpawnInfo(Pair.Key, EventInfo->PositionOnGraph, RelativePositionsToConnect, PositionsToConnect);
		}
	}
}

void UEventGraph::UpdateEventGraphNode(const FGameplayTag& EventTag, const FExperiencedEventInfo& ExperiencedEventInfo, bool bGenerated, const FVector2D& PositionOnGraph)
{
	check(EventGraphNodeClass);

	if (!bGenerated)
	{
		UEventGraphNode* NewEventGraphNode = CreateWidget<UEventGraphNode>(this, EventGraphNodeClass);
		CanvasPanel_Root->AddChild(NewEventGraphNode);

		UCanvasPanelSlot* CanvasPanelSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(NewEventGraphNode);
		CanvasPanelSlot->SetAnchors(FAnchors(0.5f, 0.5f));
		CanvasPanelSlot->SetAlignment(FVector2D(0.5f, 0.5f));
		CanvasPanelSlot->SetPosition(PositionOnGraph);
		CanvasPanelSlot->SetAutoSize(true);

		NewEventGraphNode->UpdateNode(EventTag, ExperiencedEventInfo);

		GeneratedEventGraphNodes.Add(EventTag, NewEventGraphNode);
	}
	else
	{
		if (UEventGraphNode* EventGraphNode = GeneratedEventGraphNodes.FindRef(EventTag).Get())
		{
			EventGraphNode->UpdateNode(EventTag, ExperiencedEventInfo);
		}
	}
}

UMemoryEventSet* UEventGraph::GetEventSet()
{
	if (!EventSet)
	{
		if (UMemoryGameInstance* MemoryGI = GetGameInstance<UMemoryGameInstance>())
		{
			EventSet = MemoryGI->GetMemoryEventSet();
		}
	}

	return EventSet;
}