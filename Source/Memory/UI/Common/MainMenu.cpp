// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"
#include "Input/CommonUIInputTypes.h"//
#include "CommonButtonBase.h"//
#include "Memory/MemoryGameplayTag.h"//

UMainMenu::UMainMenu(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	InputConfig = EMemoryWidgetInputMode::Menu;
	MouseCaptureMode = EMouseCaptureMode::CapturePermanently;
}

void UMainMenu::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	RegisterUIActionBinding(FBindUIActionArgs(FUIActionTag::ConvertChecked(TriggerTag), false,
		FSimpleDelegate::CreateUObject(this, &UMainMenu::HandleTabAction)));

	EventMenuButton->OnClicked().AddUObject(this, &UMainMenu::EventMenuButtonClicked);

	CharacterCognitionMenuButton->OnClicked().AddUObject(this, &UMainMenu::CharacterCognitionMenuButtonClicked);
}

void UMainMenu::HandleTabAction()
{
	DeactivateWidget();
}

void UMainMenu::EventMenuButtonClicked()
{
	const FMemoryGameplayTags& GameplayTags = FMemoryGameplayTags::Get();

	PushCoreWidget(GameplayTags.Widget_EventMenu, GameplayTags.Layer_Menu);
}

void UMainMenu::CharacterCognitionMenuButtonClicked()
{
	const FMemoryGameplayTags& GameplayTags = FMemoryGameplayTags::Get();

	PushCoreWidget(GameplayTags.Widget_CharacterCognitionMenu, GameplayTags.Layer_Menu);
}