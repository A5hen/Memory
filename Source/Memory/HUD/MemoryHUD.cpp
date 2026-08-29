// Fill out your copyright notice in the Description page of Project Settings.


#include "MemoryHUD.h"
#include "Blueprint/WidgetLayoutLibrary.h"//
#include "Memory/Player/MemoryPlayerState.h"//
#include "Memory/UI/Common/PrimaryGameLayout.h"//
#include "Memory/UI/Common/MemoryActivatableWidget.h"//
#include "Memory/UI/WidgetController/OverlayWidgetController.h"//
#include "Memory/UI/WidgetController/EventGraphWidgetController.h"//
#include "Memory/UI/WidgetController/CognitionGraphWidgetController.h"//
#include "Memory/MemoryGameplayTag.h"//

void AMemoryHUD::InitRootLayout()
{
	check(RootLayoutClass);
	
	if (APlayerController* PlayerController = GetOwningPlayerController())
	{
		RootLayout = CreateWidget<UPrimaryGameLayout>(PlayerController, RootLayoutClass);
		if(RootLayout)
		{
			RootLayout->AddToViewport(10);
		}
	}
}

void AMemoryHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	check(OverlayWidgetClass);

	if (!RootLayout)return;

	const FMemoryGameplayTags& GameplayTags = FMemoryGameplayTags::Get();

	if (Overlay = RootLayout->PushWidgetToLayerStack(GameplayTags.Layer_Game, OverlayWidgetClass))
	{
		Overlay->SetWidgetController(GetOverlayWidgetController());
	}
}

UPrimaryGameLayout* AMemoryHUD::GetRootLayout() const
{
	return RootLayout;
}

bool AMemoryHUD::MakeWidgetControllerParams(FWidgetControllerParams& OutParams)
{
	if (APlayerController* PC = GetOwningPlayerController())
	{
		if (AMemoryPlayerState* MemoryPS = PC->GetPlayerState<AMemoryPlayerState>())
		{
			UAbilitySystemComponent* ASC = MemoryPS->GetAbilitySystemComponent();
			UAttributeSet* AS = MemoryPS->GetAttributeSet();

			OutParams.AbilitySystemComponent = ASC;
			OutParams.AttributeSet = AS;
			OutParams.PlayerContrller = PC;
			OutParams.PlayerState = MemoryPS;

			return true;
		}
	}

	return false;
}

UMemoryWidgetController* AMemoryHUD::GetBaseWidgetController()
{
	if (BaseWidgetController == nullptr)
	{
		FWidgetControllerParams Params;
		if (MakeWidgetControllerParams(Params))
		{
			BaseWidgetController = NewObject<UMemoryWidgetController>(this, BaseWidgetControllerClass);
			BaseWidgetController->SetWidgetControllerParams(Params);
		}
	}

	return BaseWidgetController;
}

UMemoryWidgetController* AMemoryHUD::GetOverlayWidgetController()
{
	check(OverlayWidgetControllerClass);

	if (OverlayWidgetController == nullptr)
	{
		FWidgetControllerParams Params;
		if (MakeWidgetControllerParams(Params))
		{
			OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
			OverlayWidgetController->SetWidgetControllerParams(Params);
			OverlayWidgetController->BindCallBacksToDependencies();
		}
	}

	return OverlayWidgetController;
}

UMemoryWidgetController* AMemoryHUD::GetEventGraphWidgetController()
{
	check(EventGraphWidgetControllerClass);

	if (EventGraphWidgetController == nullptr)
	{
		FWidgetControllerParams Params;
		if (MakeWidgetControllerParams(Params))
		{
			EventGraphWidgetController = NewObject<UEventGraphWidgetController>(this, EventGraphWidgetControllerClass);
			EventGraphWidgetController->SetWidgetControllerParams(Params);
			EventGraphWidgetController->BindCallBacksToDependencies();
		}
	}

	return EventGraphWidgetController;
}

UMemoryWidgetController* AMemoryHUD::GetCognitionGraphWidgetController()
{
	check(CognitionGraphWidgetControllerClass);

	if (CognitionGraphWidgetController == nullptr)
	{
		FWidgetControllerParams Params;
		if (MakeWidgetControllerParams(Params))
		{
			CognitionGraphWidgetController = NewObject<UCognitionGraphWidgetController>(this, CognitionGraphWidgetControllerClass);
			CognitionGraphWidgetController->SetWidgetControllerParams(Params);
			CognitionGraphWidgetController->BindCallBacksToDependencies();
		}
	}

	return CognitionGraphWidgetController;
}

const TSubclassOf<UMemoryActivatableWidget>* AMemoryHUD::GetCoreWidgetClass(const FGameplayTag& WidgetTag) const
{
	return CoreWidgetClasses.Find(WidgetTag);
}

void AMemoryHUD::PushMainMenu()
{
	check(MainMenuClass);

	if (!RootLayout)return;

	const FMemoryGameplayTags& GameplayTags = FMemoryGameplayTags::Get();

	UMemoryActivatableWidget* MainMenu = RootLayout->PushWidgetToLayerStack(GameplayTags.Layer_Menu, MainMenuClass);
	if (MainMenu)
	{
		MainMenu->SetWidgetController(GetBaseWidgetController());
	}
}