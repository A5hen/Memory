// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterCognitionGraph.h"
#include "Components/CanvasPanel.h"//
#include "Components/CanvasPanelSlot.h"//
#include "Blueprint/WidgetLayoutLibrary.h"//
#include "Memory/GameInstance/MemoryGameInstance.h"//
#include "Memory/Player/MemoryPlayerState.h"//
#include "Memory/Player/Cognition/CharacterCognitionSet.h"//
#include "Memory/UI/CognitionGraph/CognitionGraphNode.h"//

void UCharacterCognitionGraph::ClearGraph()
{
	for (auto& Pair : GeneratedCognitionGraphNodes)
	{
		if (Pair.Value)
		{
			Pair.Value->RemoveFromParent();
		}
	}

	GeneratedCognitionGraphNodes.Empty();

	CharacterTag = FGameplayTag();

	Super::ClearGraph();
}

FVector2D UCharacterCognitionGraph::JumptoCognitionGraphNode(FName BehaviorDec)
{
	if (UCognitionGraphNode* TargetNode = GeneratedCognitionGraphNodes.FindRef(BehaviorDec).Get())
	{
		UCanvasPanelSlot* CanvasPanelSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(TargetNode);
		return CanvasPanelSlot->GetPosition();
	}

	return FVector2D();
}

void UCharacterCognitionGraph::UpdateCognitionGraph(const FGeneratedBehavior& GeneratedBehavior)
{
	check(CognitionGraphNodeClass);

	if (!GetCharacterCognitionSet())return;

	for (const auto& Pair : GeneratedBehavior.DescToCognition)
	{
		if (UCognitionGraphNode* CognitionGraphNode = GeneratedCognitionGraphNodes.FindRef(Pair.Key).Get())
		{
			CognitionGraphNode->UpdateNode(CharacterTag, Pair.Key, Pair.Value);	
		}
		else
		{
			if (const FBehaviorCognition* BehaviorCognition = CharacterCognitionSet->GetBehaviorCognition(CharacterTag, Pair.Key))
			{
				UCognitionGraphNode* NewCognitionGraphNode = CreateWidget<UCognitionGraphNode>(this, CognitionGraphNodeClass);
				CanvasPanel_Root->AddChild(NewCognitionGraphNode);

				UCanvasPanelSlot* CanvasPanelSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(NewCognitionGraphNode);
				CanvasPanelSlot->SetAnchors(FAnchors(0.5f, 0.5f));
				CanvasPanelSlot->SetAlignment(FVector2D(0.5f, 0.5f));
				CanvasPanelSlot->SetPosition(BehaviorCognition->PositionOnGraph);
				CanvasPanelSlot->SetAutoSize(true);

				NewCognitionGraphNode->UpdateNode(CharacterTag, Pair.Key, Pair.Value);

				GeneratedCognitionGraphNodes.Add(Pair.Key, NewCognitionGraphNode);
			}
		}
	}
}

UCognitionGraphNode* UCharacterCognitionGraph::GetCognitionGraphNode(FName BehaviorDesc)
{
	return GeneratedCognitionGraphNodes.FindRef(BehaviorDesc).Get();
}

UCharacterCognitionSet* UCharacterCognitionGraph::GetCharacterCognitionSet()
{
	if (!CharacterCognitionSet)
	{
		if (UMemoryGameInstance* MemoryGI = GetGameInstance<UMemoryGameInstance>())
		{
			CharacterCognitionSet = MemoryGI->GetCharacterCognitionSet();
		}
	}

	return CharacterCognitionSet;
}