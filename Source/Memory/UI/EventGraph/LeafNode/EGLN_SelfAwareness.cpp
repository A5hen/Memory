// Fill out your copyright notice in the Description page of Project Settings.


#include "EGLN_SelfAwareness.h"
#include "Components/ScrollBox.h"//
#include "Memory/UI/GraphContentWidget.h"//
#include "Memory/MemoryGameplayTag.h"//

void UEGLN_SelfAwareness::UpdateContent(const FGameplayTag& EventTag, const FGameplayTagContainer& GeneratedSelfAwareness)
{
	check(OverviewClass_SelfAwareness);
	
	const FMemoryGameplayTags& GameplayTags = FMemoryGameplayTags::Get();

	ScrollBox_SelfAwareness->ClearChildren();

	for (const FGameplayTag& SelfAwareness : GeneratedSelfAwareness)
	{
		UGraphContentWidget* Overview_SelfAwareness = CreateWidget<UGraphContentWidget>(this, OverviewClass_SelfAwareness);
		Overview_SelfAwareness->ContentWidgetInfo.OwnerWidgetTag = GameplayTags.Widget_EventMenu;
		Overview_SelfAwareness->ContentWidgetInfo.ContentTag = GameplayTags.Content_SelfAwareness;
		Overview_SelfAwareness->ContentWidgetInfo.EventTag = EventTag;
		Overview_SelfAwareness->ContentWidgetInfo.SelfAwarenessTag = SelfAwareness;

		Overview_SelfAwareness->DisplayContent();

		ScrollBox_SelfAwareness->AddChild(Overview_SelfAwareness);
	}
}