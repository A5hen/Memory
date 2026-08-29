// Fill out your copyright notice in the Description page of Project Settings.


#include "CognitionGraphNode.h"
#include "Components/WidgetSwitcher.h"//
#include "Memory/Player/MemoryPlayerState.h"// 
#include "Memory/UI/GraphContentWidget.h"//
#include "Memory/MemoryGameplayTag.h"//

void UCognitionGraphNode::UpdateNode(const FGameplayTag& InCharactertag, const FName& InBehaviorDesc, const FBehaviorCognitionInfo& BehaviorCognitionInfo)
{
	check(ContentClass_CharacterBehavior);

	const FMemoryGameplayTags& GameplayTags = FMemoryGameplayTags::Get();

	CharacterTag = InCharactertag;
	BehaviorDesc = InBehaviorDesc;

	for (const FGameplayTag& SourceEvent : BehaviorCognitionInfo.Source)
	{
		if (SourceEvnetTags.HasTagExact(SourceEvent))continue;

		SourceEvnetTags.AddTag(SourceEvent);

		UGraphContentWidget* Content_CharacterBehavior = CreateWidget<UGraphContentWidget>(this, ContentClass_CharacterBehavior);
		Content_CharacterBehavior->ContentWidgetInfo.OwnerWidgetTag = GameplayTags.Widget_CharacterCognitionMenu;
		Content_CharacterBehavior->ContentWidgetInfo.ContentTag = GameplayTags.Content_CharacterBehavior;
		Content_CharacterBehavior->ContentWidgetInfo.CharacterTag = CharacterTag;
		Content_CharacterBehavior->ContentWidgetInfo.BehaviorDesc = BehaviorDesc;
		Content_CharacterBehavior->ContentWidgetInfo.CognitionLevel = BehaviorCognitionInfo.CurrentCognitionLevel;
		Content_CharacterBehavior->ContentWidgetInfo.EventTag = SourceEvent;

		Content_CharacterBehavior->DisplayContent();

		Switcher_Root->AddChild(Content_CharacterBehavior);
	}
}

void UCognitionGraphNode::SwitchSourceEvent(bool bNext)
{
	if (SourceEvnetTags.Num() <= 1)return;

	if (bNext)
	{
		++SwitcherIndex;
		if (SwitcherIndex >= SourceEvnetTags.Num())
		{
			SwitcherIndex = 0;
		}
	}
	else
	{
		--SwitcherIndex;
		if (SwitcherIndex <= 0)
		{
			SwitcherIndex = SourceEvnetTags.Num() - 1;
		}
	}

	Switcher_Root->SetActiveWidgetIndex(SwitcherIndex);
}