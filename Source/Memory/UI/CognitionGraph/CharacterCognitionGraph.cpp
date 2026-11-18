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

FVector2D UCharacterCognitionGraph::JumpToCognitionGraphNode(const FName& BehaviorDec)
{
	if (UCognitionGraphNode* TargetNode = GeneratedCognitionGraphNodes.FindRef(BehaviorDec).Get())
	{
		UCanvasPanelSlot* CanvasPanelSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(TargetNode);
		return CanvasPanelSlot->GetPosition();

		//TODO
	}

	return FVector2D();
}

void UCharacterCognitionGraph::UpdateCognitionGraph(const FGeneratedBehavior& GeneratedBehavior)
{
	check(CognitionGraphNodeClass);

	if (!GetCharacterCognitionSet())return;

	//TODO
	for (const auto& Pair : GeneratedBehavior.DescToCognition)
	{
		UpdateCognitionGraphNode(Pair.Key, Pair.Value);
	}
}

void UCharacterCognitionGraph::UpdateCognitionGraphNode(const FName& BehaviorDesc, const FGeneratedBehaviorCognition& GeneratedBehaviorCognition)
{
	if (UCognitionGraphNode* CognitionGraphNode = GeneratedCognitionGraphNodes.FindRef(BehaviorDesc).Get())
	{
		CognitionGraphNode->UpdateNode(CharacterTag, BehaviorDesc, GeneratedBehaviorCognition);
	}
	else
	{
		if (const FBehaviorCognition* BehaviorCognition = CharacterCognitionSet->GetBehaviorCognition(CharacterTag, BehaviorDesc))
		{
			UCognitionGraphNode* NewCognitionGraphNode = CreateWidget<UCognitionGraphNode>(this, CognitionGraphNodeClass);
			CanvasPanel_Root->AddChild(NewCognitionGraphNode);

			UCanvasPanelSlot* CanvasPanelSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(NewCognitionGraphNode);
			CanvasPanelSlot->SetAnchors(FAnchors(0.5f, 0.5f));
			CanvasPanelSlot->SetAlignment(FVector2D(0.5f, 0.5f));
			CanvasPanelSlot->SetPosition(BehaviorCognition->PositionOnGraph);
			CanvasPanelSlot->SetAutoSize(true);

			NewCognitionGraphNode->UpdateNode(CharacterTag, BehaviorDesc, GeneratedBehaviorCognition);

			GeneratedCognitionGraphNodes.Emplace(BehaviorDesc, NewCognitionGraphNode);
		}
	}
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