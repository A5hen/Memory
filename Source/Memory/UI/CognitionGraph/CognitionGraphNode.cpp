// Fill out your copyright notice in the Description page of Project Settings.


#include "CognitionGraphNode.h"
#include "Components/WidgetSwitcher.h"//
#include "Memory/Player/MemoryPlayerState.h"// 
#include "Memory/UI/GraphContentWidget.h"//
#include "Memory/MemoryGameplayTag.h"//

void UCognitionGraphNode::UpdateNode(const FGameplayTag& InCharactertag, const FName& InBehaviorDesc, const FGeneratedBehaviorCognition& GeneratedBehaviorCognition)
{
	check(ContentClass_CharacterBehavior);

	const FMemoryGameplayTags& GameplayTags = FMemoryGameplayTags::Get();

	for (const FGameplayTag& SourceEvent : GeneratedBehaviorCognition.Source)
	{
		if (UGraphContentWidget* Content_CharacterBehavior = GeneratedCharacterBehaviors.FindRef(SourceEvent).Get())
		{
			Content_CharacterBehavior->ContentWidgetInfo.CognitionLevel = GeneratedBehaviorCognition.CurrentCognitionLevel;
			Content_CharacterBehavior->UpdateContent();

			continue;
		}

		UGraphContentWidget* Content_CharacterBehavior = CreateWidget<UGraphContentWidget>(this, ContentClass_CharacterBehavior);
		Content_CharacterBehavior->ContentWidgetInfo.OwnerWidgetTag = GameplayTags.Widget_CharacterCognitionMenu;
		Content_CharacterBehavior->ContentWidgetInfo.ContentTag = GameplayTags.Content_CharacterBehavior;
		Content_CharacterBehavior->ContentWidgetInfo.CharacterTag = InCharactertag;
		Content_CharacterBehavior->ContentWidgetInfo.BehaviorDesc = InBehaviorDesc;
		Content_CharacterBehavior->ContentWidgetInfo.CognitionLevel = GeneratedBehaviorCognition.CurrentCognitionLevel;
		Content_CharacterBehavior->ContentWidgetInfo.EventTag = SourceEvent;
		Content_CharacterBehavior->UpdateContent();

		Switcher_Root->AddChild(Content_CharacterBehavior);
		GeneratedCharacterBehaviors.Add(SourceEvent, Content_CharacterBehavior);
	}
}

void UCognitionGraphNode::SwitchSourceEvent(bool bNext)
{
	int32 WidgetNum = GeneratedCharacterBehaviors.Num();

	if (WidgetNum <= 1)return;

	if (bNext)
	{
		++SwitcherIndex;
		if (SwitcherIndex >= WidgetNum)
		{
			SwitcherIndex = 0;
		}
	}
	else
	{
		--SwitcherIndex;
		if (SwitcherIndex <= 0)
		{
			SwitcherIndex = WidgetNum - 1;
		}
	}

	Switcher_Root->SetActiveWidgetIndex(SwitcherIndex);
}