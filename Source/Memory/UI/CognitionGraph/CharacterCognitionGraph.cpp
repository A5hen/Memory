// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterCognitionGraph.h"
#include "Components/CanvasPanel.h"//
#include "Components/CanvasPanelSlot.h"//
#include "Blueprint/WidgetLayoutLibrary.h"//
#include "Memory/GameInstance/MemoryGameInstance.h"//
#include "Memory/Player/MemoryPlayerState.h"//
#include "Memory/Player/Cognition/CharacterCognitionSet.h"//
#include "Memory/UI/WidgetController/CognitionGraphWidgetController.h"//
#include "Memory/UI/CognitionGraph/CognitionGraphNode.h"//

void UCharacterCognitionGraph::SetWidgetController(UMemoryWidgetController* InWidgetController)
{
	WidgetController = InWidgetController;

	UCognitionGraphWidgetController* CognitionGraphWidgetController = Cast<UCognitionGraphWidgetController>(InWidgetController);
	if (CognitionGraphWidgetController)
	{
		SelectedCharacter = CognitionGraphWidgetController->GetSelectedCharacter();

		CognitionGraphWidgetController->UpdateCognitionGraph.AddUObject(this, &UCharacterCognitionGraph::UpdateCognitionGraph);
		CognitionGraphWidgetController->BroadcastInitialValues();
	}
}

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

	SelectedCharacter = FGameplayTag();

	Super::ClearGraph();
}

void UCharacterCognitionGraph::UnbindCallBacks()
{
	if (UCognitionGraphWidgetController* CognitionGraphWidgetController = Cast<UCognitionGraphWidgetController>(WidgetController))
	{
		CognitionGraphWidgetController->UpdateCognitionGraph.RemoveAll(this);
	}
}

void UCharacterCognitionGraph::UpdateCognitionGraph(const FBehaviorCognitionInfomation& BehaviorCognitionInfomation)
{
	check(CognitionGraphNodeClass);

	if (!GetCharacterCognitionSet())return;

	for (const auto& Pair : BehaviorCognitionInfomation.DescToInfo)
	{
		if (GeneratedCognitionGraphNodes.Find(Pair.Key))
		{
			UCognitionGraphNode* CognitionGraphNode = GeneratedCognitionGraphNodes[Pair.Key];
			CognitionGraphNode->UpdateNode(SelectedCharacter, Pair.Key, Pair.Value);	
		}
		else
		{
			if (const FBehaviorCognition* BehaviorCognition = CharacterCognitionSet->GetBehaviorCognition(SelectedCharacter, Pair.Key))
			{
				UCognitionGraphNode* CognitionGraphNode = CreateWidget<UCognitionGraphNode>(this, CognitionGraphNodeClass);
				CanvasPanel_Root->AddChild(CognitionGraphNode);

				UCanvasPanelSlot* CanvasPanelSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(CognitionGraphNode);
				CanvasPanelSlot->SetAnchors(FAnchors(0.5f, 0.5f));
				CanvasPanelSlot->SetAlignment(FVector2D(0.5f, 0.5f));
				CanvasPanelSlot->SetPosition(BehaviorCognition->PositionOnGraph);
				CanvasPanelSlot->SetAutoSize(true);

				CognitionGraphNode->UpdateNode(SelectedCharacter, Pair.Key, Pair.Value);

				GeneratedCognitionGraphNodes.Add(Pair.Key, CognitionGraphNode);
			}
		}
	}
}

UCharacterCognitionSet* UCharacterCognitionGraph::GetCharacterCognitionSet()
{
	if (UMemoryGameInstance* MemoryGI = GetGameInstance<UMemoryGameInstance>())
	{
		CharacterCognitionSet = MemoryGI->GetCharacterCognitionSet();
	}

	return CharacterCognitionSet;
}