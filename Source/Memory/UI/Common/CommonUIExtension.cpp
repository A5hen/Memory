// Fill out your copyright notice in the Description page of Project Settings.


#include "CommonUIExtension.h"
#include "CommonInputSubsystem.h"//
#include "CommonInputTypeEnum.h"//
#include "Memory/HUD/MemoryHUD.h"//
#include "Memory/UI/Common/PrimaryGameLayout.h"//
#include "Memory/UI/Common/MemoryActivatableWidget.h"//
#include "Memory/UI/Common/CommonUIInterface.h"//

int32 UCommonUIExtension::InputSuspensions = 0;

UMemoryActivatableWidget* UCommonUIExtension::PushContentToLayerForPlayer(
	APlayerController* PlayerController, FGameplayTag LayerTag, TSubclassOf<UMemoryActivatableWidget> WidgetClass)
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

UMemoryActivatableWidget* UCommonUIExtension::PushCoreWidgetToLayerForPlayer(
	APlayerController* PlayerController, FGameplayTag WidgetTag, FGameplayTag LayerTag)
{
	if (!PlayerController)return nullptr;

	AMemoryHUD* MemoryHUD = Cast<AMemoryHUD>(PlayerController->GetHUD());
	if (MemoryHUD)
	{
		UPrimaryGameLayout* RootLayout = MemoryHUD->GetRootLayout();
		if (RootLayout)
		{
			for (UCommonActivatableWidget* WidgetInLayer : RootLayout->GetWidgetsInLayer(LayerTag))
			{
				if (UMemoryActivatableWidget* Widget = Cast<UMemoryActivatableWidget>(WidgetInLayer))
				{
					if (Widget->GetWidgetTag().MatchesTagExact(WidgetTag))
					{
						if (Widget->IsActivated())
						{
							return Widget;
						}
						else
						{
							RootLayout->FindAndRemoveWidgetFromLayer(LayerTag, Widget);
						}
					}
				}
			}

			const TSubclassOf<UMemoryActivatableWidget>* WidgetClassPtr = MemoryHUD->GetCoreWidgetClass(WidgetTag);
			if (WidgetClassPtr)
			{
				return RootLayout->PushWidgetToLayerStack(LayerTag, *WidgetClassPtr);
			}
		}
	}

	return nullptr;
}

void UCommonUIExtension::PushStreamedContentToLayerForPlayer(
	APlayerController* PlayerController, FGameplayTag LayerTag, TSoftClassPtr<UMemoryActivatableWidget> WidgetSoftClassPtr)
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

void UCommonUIExtension::PopContentFromLayer(APlayerController* PlayerController, FGameplayTag LayerTag, UMemoryActivatableWidget* ActivatableWidget)
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