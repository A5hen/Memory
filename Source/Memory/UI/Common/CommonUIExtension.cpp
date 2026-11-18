// Fill out your copyright notice in the Description page of Project Settings.


#include "CommonUIExtension.h"
#include "CommonInputSubsystem.h"//
#include "CommonInputTypeEnum.h"//
#include "CommonActivatableWidget.h"//
#include "Memory/HUD/MemoryHUD.h"//
#include "Memory/UI/Common/PrimaryGameLayout.h"//
#include "Memory/MemoryGameplayTag.h"//

int32 UCommonUIExtension::InputSuspensions = 0;

UPrimaryGameLayout* UCommonUIExtension::GetPrimaryGameLayout(APlayerController* PlayerController)
{
	if (!PlayerController)return nullptr;

	AMemoryHUD* MemoryHUD = Cast<AMemoryHUD>(PlayerController->GetHUD());
	if (MemoryHUD)
	{
		return MemoryHUD->GetRootLayout();
	}

	return nullptr;
}

UCommonActivatableWidget* UCommonUIExtension::PushContentToLayerForPlayer(
	APlayerController* PlayerController, FGameplayTag LayerTag, TSubclassOf<UCommonActivatableWidget> WidgetClass)
{
	if (!PlayerController)return nullptr;

	AMemoryHUD* MemoryHUD = Cast<AMemoryHUD>(PlayerController->GetHUD());
	if (MemoryHUD)
	{
		UPrimaryGameLayout* RootLayout = MemoryHUD->GetRootLayout();
		if (RootLayout)
		{
			return RootLayout->PushWidgetToLayerStack(LayerTag, WidgetClass);
		}	
	}

	return nullptr;
}

void UCommonUIExtension::PushStreamedContentToLayerForPlayer(
	APlayerController* PlayerController, FGameplayTag LayerTag, TSoftClassPtr<UCommonActivatableWidget> WidgetSoftClassPtr)
{
	if (!PlayerController)return;

	AMemoryHUD* MemoryHUD = Cast<AMemoryHUD>(PlayerController->GetHUD());
	if (MemoryHUD)
	{
		UPrimaryGameLayout* RootLayout = MemoryHUD->GetRootLayout();
		if (RootLayout)
		{
			RootLayout->PushWidgetToLayerStackAsync(LayerTag, true, WidgetSoftClassPtr);
		}
	}
}

UCommonActivatableWidget* UCommonUIExtension::PushExplanationToLayerForPlayer(APlayerController* PlayerController)
{
	if (!PlayerController)return nullptr;

	const FMemoryGameplayTags& GameplayTags = FMemoryGameplayTags::Get();

	AMemoryHUD* MemoryHUD = Cast<AMemoryHUD>(PlayerController->GetHUD());
	if (MemoryHUD)
	{
		UPrimaryGameLayout* RootLayout = MemoryHUD->GetRootLayout();
		if (RootLayout)
		{
			//return RootLayout->PushWidgetToLayerStack(GameplayTags.Layer_Cue, WidgetClass);
		}
	}

	return nullptr;
}

UWidget* UCommonUIExtension::SwitchToCoreWidgetForPlayer(APlayerController* PlayerController, FGameplayTag CoreWidgetTag)
{
	if (!PlayerController)return nullptr;

	const FMemoryGameplayTags& GameplayTags = FMemoryGameplayTags::Get();

	AMemoryHUD* MemoryHUD = Cast<AMemoryHUD>(PlayerController->GetHUD());
	if (MemoryHUD)
	{
		UPrimaryGameLayout* RootLayout = MemoryHUD->GetRootLayout();
		if (RootLayout)
		{
			return RootLayout->SwitchToCoreWidget(CoreWidgetTag);
		}
	}

	return nullptr;
}

void UCommonUIExtension::PopContentFromLayer(APlayerController* PlayerController, FGameplayTag LayerTag, UCommonActivatableWidget* ActivatableWidget)
{
	if (!PlayerController || !ActivatableWidget)return;

	AMemoryHUD* MemoryHUD = Cast<AMemoryHUD>(PlayerController->GetHUD());
	if (MemoryHUD)
	{
		UPrimaryGameLayout* RootLayout = MemoryHUD->GetRootLayout();
		if (RootLayout)
		{
			RootLayout->FindAndRemoveWidgetFromLayer(LayerTag, ActivatableWidget);
		}
	}
}

FName UCommonUIExtension::SuspendInputForPlayer(APlayerController* PlayerController, FName SuspendReason)
{
	ULocalPlayer* LocalPlayer = PlayerController ? PlayerController->GetLocalPlayer() : nullptr;
	if (UCommonInputSubsystem* CommonInputSubsystem = UCommonInputSubsystem::Get(LocalPlayer))
	{
		InputSuspensions++;
		FName SuspendToken = SuspendReason;
		SuspendToken.SetNumber(InputSuspensions);

		CommonInputSubsystem->SetInputTypeFilter(ECommonInputType::MouseAndKeyboard, SuspendToken, true);
		CommonInputSubsystem->SetInputTypeFilter(ECommonInputType::Gamepad, SuspendToken, true);
		CommonInputSubsystem->SetInputTypeFilter(ECommonInputType::Touch, SuspendToken, true);

		return SuspendToken;
	}

	return NAME_None;
}

void UCommonUIExtension::ResumeInputForPlayer(APlayerController* PlayerController, FName SuspendToken)
{
	if (SuspendToken == NAME_None)
	{
		return;
	}

	ULocalPlayer* LocalPlayer = PlayerController ? PlayerController->GetLocalPlayer() : nullptr;
	if (UCommonInputSubsystem* CommonInputSubsystem = UCommonInputSubsystem::Get(LocalPlayer))
	{
		CommonInputSubsystem->SetInputTypeFilter(ECommonInputType::MouseAndKeyboard, SuspendToken, false);
		CommonInputSubsystem->SetInputTypeFilter(ECommonInputType::Gamepad, SuspendToken, false);
		CommonInputSubsystem->SetInputTypeFilter(ECommonInputType::Touch, SuspendToken, false);
	}
}