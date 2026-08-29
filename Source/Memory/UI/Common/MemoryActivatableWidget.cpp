// Fill out your copyright notice in the Description page of Project Settings.


#include "MemoryActivatableWidget.h"
#include "Memory/AbilitySystem/MemoryAbilitySystemLibrary.h"
#include "Memory/UI/WidgetController/MemoryWidgetController.h"//
#include "Memory/UI/Common/CommonUIExtension.h"//
#include "Memory/MemoryGameplayTag.h"//

TOptional<FUIInputConfig> UMemoryActivatableWidget::GetDesiredInputConfig() const
{
	switch (InputConfig)
	{
	case EMemoryWidgetInputMode::GameAndMenu:
		return FUIInputConfig(ECommonInputMode::All, MouseCaptureMode);

	case EMemoryWidgetInputMode::Game:
		return FUIInputConfig(ECommonInputMode::Game, MouseCaptureMode);

	case EMemoryWidgetInputMode::Menu:
		return FUIInputConfig(ECommonInputMode::Menu, EMouseCaptureMode::NoCapture);

	case EMemoryWidgetInputMode::Default:

	default:
		return TOptional<FUIInputConfig>();
	}
}

const FGameplayTag& UMemoryActivatableWidget::GetWidgetTag() const
{
	return WidgetTag;
}

void UMemoryActivatableWidget::SetOwnerActorTag(const FGameplayTag& ActorTag)
{
	OwnerActorTag = ActorTag;
}

void UMemoryActivatableWidget::SetWidgetController(UMemoryWidgetController* InWidgetController)
{
	WidgetController = InWidgetController;
}

void UMemoryActivatableWidget::NativeOnActivated()
{
	Super::NativeOnActivated();
}

void UMemoryActivatableWidget::NativeOnDeactivated()
{
	OwnerActorTag = FGameplayTag();

	if (bReactContentSelection && WidgetController)
	{
		bReactContentSelection = false;

		WidgetController->OnContentSelected.RemoveAll(this);
	}

	Super::NativeOnDeactivated();
}

UMemoryActivatableWidget* UMemoryActivatableWidget::PushCoreWidget(const FGameplayTag& InWidgetTag, const FGameplayTag& LayerTag)
{
	if (!InWidgetTag.IsValid() || !LayerTag.IsValid())return nullptr;

	if (WidgetController)
	{
		UMemoryActivatableWidget* CoreWidget = UCommonUIExtension::PushCoreWidgetToLayerForPlayer(WidgetController->PlayerController, InWidgetTag, LayerTag);
		return CoreWidget;
	}

	return nullptr;
}

void UMemoryActivatableWidget::JumpToCoreWidget()
{
	if (!bReactContentSelection || !TargetCoreWidget.IsValid())return;

	const FMemoryGameplayTags& GameplayTags = FMemoryGameplayTags::Get();

	PushCoreWidget(TargetCoreWidget, GameplayTags.Layer_Menu);

	//TODO
}

void UMemoryActivatableWidget::OnContentSelected(const FContentWidgetInfo& ContentWidgetInfo)
{
	const FMemoryGameplayTags& GameplayTags = FMemoryGameplayTags::Get();

	if (ContentWidgetInfo.ContentTag.MatchesTagExact(GameplayTags.Content_Event))
	{
		TargetCoreWidget = GameplayTags.Widget_EventMenu;
	}

	if (ContentWidgetInfo.ContentTag.MatchesTagExact(GameplayTags.Content_Character) ||
		ContentWidgetInfo.ContentTag.MatchesTagExact(GameplayTags.Content_CharacterBehavior))
	{
		TargetCoreWidget = GameplayTags.Widget_CharacterCognitionMenu;
	}

	if (ContentWidgetInfo.ContentTag.MatchesTagExact(GameplayTags.Content_SelfAwareness))
	{
		TargetCoreWidget = GameplayTags.Widget_SelfAwarenessMenu;
	}
}

void UMemoryActivatableWidget::ReactContentSelection()
{
	if (WidgetController)
	{
		bReactContentSelection = true;

		WidgetController->OnContentSelected.AddUObject(this, &UMemoryActivatableWidget::OnContentSelected);
	}
}