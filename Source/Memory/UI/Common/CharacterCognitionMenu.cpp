// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterCognitionMenu.h"
#include "Components/ScrollBox.h"//
#include "Memory/UI/WidgetController/CognitionGraphWidgetController.h"//
#include "Memory/UI/CognitionGraph/CharacterCognitionGraph.h"//
#include "Memory/UI/CognitionGraph/BehaviorCognitionDetail.h"//
#include "Memory/UI/GraphContentWidget.h"//
#include "Memory/AbilitySystem/MemoryAbilitySystemLibrary.h"//
#include "Memory/MemoryGameplayTag.h"//

void UCharacterCognitionMenu::SetWidgetController(UMemoryWidgetController* InWidgetController)
{
	Super::SetWidgetController(InWidgetController);

	UCognitionGraphWidgetController* CognitionGraphWidgetController = Cast<UCognitionGraphWidgetController>(WidgetController);
	if (CognitionGraphWidgetController)
	{
		CharacterCognitionGraph->SetWidgetController(WidgetController);

		UpdateCharacterSwitcher(CognitionGraphWidgetController->GetSelectableCharacters());
	}
}

void UCharacterCognitionMenu::TestJumpFunction()
{
	const FMemoryGameplayTags& GameplayTags = FMemoryGameplayTags::Get();
	PushCoreWidget(GameplayTags.Widget_EventMenu, GameplayTags.Layer_Menu);
}

void UCharacterCognitionMenu::NativeOnActivated()
{
	if (!WidgetController)
	{
		if (UMemoryWidgetController* CognitionGraphWidgetController = UMemoryAbilitySystemLibrary::GetCognitionGraphWidgetController(this))
		{
			SetWidgetController(CognitionGraphWidgetController);
		}
	}
	else
	{

	}

	ReactContentSelection();

	Super::NativeOnActivated();
}

void UCharacterCognitionMenu::NativeOnDeactivated()
{
	ScrollBox_Character->ClearChildren();

	CharacterCognitionGraph->UnbindCallBacks();

	bMouseDown = false;

	MousePosition = FVector2D::ZeroVector;
	MousePositionLastFrame = FVector2D::ZeroVector;

	Super::NativeOnDeactivated();
}

FReply UCharacterCognitionMenu::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	MousePosition = InMouseEvent.GetScreenSpacePosition();
	bMouseDown = true;

	return FReply::Handled();
}

FReply UCharacterCognitionMenu::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	bMouseDown = false;

	return FReply::Handled();
}

FReply UCharacterCognitionMenu::NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (bMouseDown)
	{
		MousePositionLastFrame = MousePosition;
		MousePosition = InMouseEvent.GetScreenSpacePosition();

		FVector2D DeltaPosition = (MousePosition - MousePositionLastFrame);

		FWidgetTransform NewTransform = CharacterCognitionGraph->GetRelativeTransform();
		NewTransform.Translation += DeltaPosition;

		GraphOffset += DeltaPosition;

		CharacterCognitionGraph->SetRelativeTransform(NewTransform);
	}

	return FReply::Handled();
}

void UCharacterCognitionMenu::OnContentSelected(const FContentWidgetInfo& ContentWidgetInfo)
{
	Super::OnContentSelected(ContentWidgetInfo);

	const FMemoryGameplayTags& GameplayTags = FMemoryGameplayTags::Get();

	if (ContentWidgetInfo.ContentTag.MatchesTagExact(GameplayTags.Content_CharacterBehavior))
	{
		ShowDetail();

		BehaviorCognitionDetail->UpdateContent(ContentWidgetInfo);
	}
}

void UCharacterCognitionMenu::UpdateCharacterSwitcher(const FGameplayTagContainer& CharacterTags)
{
	check(OverviewClass_Character);

	const FMemoryGameplayTags& GameplayTags = FMemoryGameplayTags::Get();

	for (const FGameplayTag& CharacterTag : CharacterTags)
	{
		if (SelectableCharacterTags.HasTagExact(CharacterTag))continue;

		UGraphContentWidget* Overview_Character = CreateWidget<UGraphContentWidget>(this, OverviewClass_Character);
		Overview_Character->ContentWidgetInfo.OwnerWidgetTag = GameplayTags.Widget_CharacterCognitionMenu;
		Overview_Character->ContentWidgetInfo.ContentTag = GameplayTags.Content_Character;
		Overview_Character->ContentWidgetInfo.CharacterTag = CharacterTag;

		Overview_Character->OnSelected.AddUObject(this, &UCharacterCognitionMenu::OnCharacterSelected);

		Overview_Character->DisplayContent();

		ScrollBox_Character->AddChild(Overview_Character);
		SelectableCharacterTags.AddTag(CharacterTag);
	}
}

void UCharacterCognitionMenu::OnCharacterSelected(const FContentWidgetInfo& ContentWidgetInfo)
{

}