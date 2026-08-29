// Fill out your copyright notice in the Description page of Project Settings.


#include "PrimaryGameLayout.h"
#include "Memory/UI/Common/CommonUIExtension.h"//
#include "Memory/UI/Common/MemoryActivatableWidget.h"//

void UPrimaryGameLayout::FindAndRemoveWidgetFromLayer(FGameplayTag LayerTag, UMemoryActivatableWidget* ActivatableWidget)
{
	if (UCommonActivatableWidgetContainerBase* Layer = GetLayerWidget(LayerTag))
	{
		Layer->RemoveWidget(*ActivatableWidget);
	}
}

UCommonActivatableWidgetContainerBase* UPrimaryGameLayout::GetLayerWidget(FGameplayTag LayerTag)
{
	return *Layers.Find(LayerTag);
}

void UPrimaryGameLayout::RegisterLayer(FGameplayTag LayerTag, UCommonActivatableWidgetContainerBase* LayerWidget)
{
	if (!IsDesignTime())
	{
		LayerWidget->OnTransitioningChanged.AddUObject(this, &UPrimaryGameLayout::OnWidgetStackTransitioning);
		LayerWidget->SetTransitionDuration(0.0);
		Layers.Add(LayerTag, LayerWidget);
	}
}

void UPrimaryGameLayout::OnWidgetStackTransitioning(UCommonActivatableWidgetContainerBase* Widget, bool bIsTransitioning)
{
	if (bIsTransitioning)
	{
		const FName SuspendToken = UCommonUIExtension::SuspendInputForPlayer(GetOwningPlayer(), TEXT("GlobalStackTransion"));
		SuspendInputTokens.Add(SuspendToken);
	}
	else
	{
		if (SuspendInputTokens.Num() > 0)
		{
			const FName SuspendToken = SuspendInputTokens.Pop();
			UCommonUIExtension::ResumeInputForPlayer(GetOwningPlayer(), SuspendToken);
		}
	}
}