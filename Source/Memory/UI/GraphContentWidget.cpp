// Fill out your copyright notice in the Description page of Project Settings.


#include "GraphContentWidget.h"
#include "Memory/MemoryGameplayTag.h"//
#include "Memory/AbilitySystem/MemoryAbilitySystemLibrary.h"//
#include "Memory/UI/WidgetController/MemoryWidgetController.h"//

void UGraphContentWidget::HandleMouseButtonDown()
{
	const FMemoryGameplayTags& GameplayTags = FMemoryGameplayTags::Get();

	if (!WidgetController)
	{
		if (ContentWidgetInfo.OwnerWidgetTag.MatchesTagExact(GameplayTags.Widget_EventMenu))
		{
			WidgetController = UMemoryAbilitySystemLibrary::GetEventGraphWidgetController(this);
		}

		if (ContentWidgetInfo.OwnerWidgetTag.MatchesTagExact(GameplayTags.Widget_CharacterCognitionMenu))
		{
			WidgetController = UMemoryAbilitySystemLibrary::GetCognitionGraphWidgetController(this);
		}

		if (ContentWidgetInfo.OwnerWidgetTag.MatchesTagExact(GameplayTags.Widget_SelfAwarenessMenu))
		{

		}
	}

	if (!WidgetController)return;

	bSelected = true;

	WidgetController->SelectContent(ContentWidgetInfo);

	OnSelected.Broadcast(ContentWidgetInfo);
	BP_OnSelected.Broadcast();
}

void UGraphContentWidget::DisplayContent()
{
	//TODO:

	DisplayContentDelegate.Broadcast(ContentDisplayInfo);
}

FReply UGraphContentWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	HandleMouseButtonDown();

	return FReply::Handled();
}