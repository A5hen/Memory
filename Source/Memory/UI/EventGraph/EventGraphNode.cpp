// Fill out your copyright notice in the Description page of Project Settings.


#include "EventGraphNode.h"
#include "Components/CanvasPanel.h"//
#include "Components/CanvasPanelSlot.h"//
#include "Blueprint/WidgetLayoutLibrary.h"//
#include "Memory/Player/MemoryPlayerState.h"//
#include "Memory/UI/EventGraph/LeafNode/EGLN_CharacterBehavior.h"//
#include "Memory/UI/EventGraph/LeafNode/EGLN_SelfAwareness.h"//
#include "Memory/MemoryGameplayTag.h"//

void UEventGraphNode::UpdateLeafNode(const FGameplayTag& EventTag, const FExperiencedEventInfo& ExperiencedEventInfo)
{
	UpdateLeafNode_CharacterBehavior(EventTag, ExperiencedEventInfo);
	UpdateLeafNode_SelfAwareness(EventTag, ExperiencedEventInfo);
}

void UEventGraphNode::UpdateLeafNode_CharacterBehavior(const FGameplayTag& EventTag, const FExperiencedEventInfo& ExperiencedEventInfo)
{
	check(LeafNode_CharacterBehaviorClass);

	const FMemoryGameplayTags& GameplayTags = FMemoryGameplayTags::Get();

	if (ExperiencedEventInfo.GeneratedCharacterBehavior.Num() != 0)
	{
		if(!LeafNode_CharacterBehavior)
		{
			LeafNode_CharacterBehavior = CreateWidget<UEGLN_CharacterBehavior>(this, LeafNode_CharacterBehaviorClass);
			CanvasPanel_Root->AddChild(LeafNode_CharacterBehavior);

			UCanvasPanelSlot* CanvasPanelSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(LeafNode_CharacterBehavior);
			CanvasPanelSlot->SetAnchors(FAnchors(0.5f, 0.5f));
			CanvasPanelSlot->SetAlignment(FVector2D(0.5f, 0.5f));

			FVector2D Position = FVector2D::ZeroVector;
			if (ExperiencedEventInfo.RelativePositions.Find(GameplayTags.Content_CharacterBehavior))
			{
				Position = ExperiencedEventInfo.RelativePositions[GameplayTags.Content_CharacterBehavior];
			}
			CanvasPanelSlot->SetPosition(Position);

			CanvasPanelSlot->SetAutoSize(true);

			TMap<FGameplayTag, TArray<FName>> CharacterBehavior;
			for (const auto& Pair : ExperiencedEventInfo.GeneratedCharacterBehavior)
			{
				CharacterBehavior.Add(Pair.Key, Pair.Value.Names);
			}
			LeafNode_CharacterBehavior->UpdateContent(EventTag, CharacterBehavior);
		}
		else
		{
			TMap<FGameplayTag, TArray<FName>> CharacterBehavior;
			for (const auto& Pair : ExperiencedEventInfo.GeneratedCharacterBehavior)
			{
				CharacterBehavior.Add(Pair.Key, Pair.Value.Names);
			}
			LeafNode_CharacterBehavior->UpdateContent(EventTag, CharacterBehavior);
		}
	}
}

void UEventGraphNode::UpdateLeafNode_SelfAwareness(const FGameplayTag& EventTag, const FExperiencedEventInfo& ExperiencedEventInfo)
{
	check(LeafNode_SelfAwarenessClass);

	const FMemoryGameplayTags& GameplayTags = FMemoryGameplayTags::Get();

	if (ExperiencedEventInfo.GeneratedSelfAwareness.Num() != 0)
	{
		if (!LeafNode_SelfAwareness)
		{
			LeafNode_SelfAwareness = CreateWidget<UEGLN_SelfAwareness>(this, LeafNode_SelfAwarenessClass);
			CanvasPanel_Root->AddChild(LeafNode_SelfAwareness);

			UCanvasPanelSlot* CanvasPanelSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(LeafNode_SelfAwareness);
			CanvasPanelSlot->SetAnchors(FAnchors(0.5f, 0.5f));
			CanvasPanelSlot->SetAlignment(FVector2D(0.5f, 0.5f));

			FVector2D Position = FVector2D::ZeroVector;
			if (ExperiencedEventInfo.RelativePositions.Find(GameplayTags.Content_SelfAwareness))
			{
				Position = ExperiencedEventInfo.RelativePositions[GameplayTags.Content_SelfAwareness];
			}
			CanvasPanelSlot->SetPosition(Position);

			CanvasPanelSlot->SetAutoSize(true);

			LeafNode_SelfAwareness->UpdateContent(EventTag, ExperiencedEventInfo.GeneratedSelfAwareness);
		}
		else
		{
			LeafNode_SelfAwareness->UpdateContent(EventTag, ExperiencedEventInfo.GeneratedSelfAwareness);
		}
	}
}