// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "GameplayTagContainer.h"//
#include "Engine/AssetManager.h"//
#include "Engine/StreamableManager.h"//
#include "CommonActivatableWidget.h"//
#include "Widgets/CommonActivatableWidgetContainer.h"//
#include "Memory/UI/Common/CommonUIExtension.h"//
#include "Memory/MemoryGameplayTag.h"//
#include "PrimaryGameLayout.generated.h"

class UCommonActivatableWidgetContainerBase;
class UMemoryActivatableWidget;

enum class EAsyncWidgetLayerState : uint8
{
	Canceled,
	Initialize,
	AfterPush
};

/**
 * 
 */
UCLASS()
class MEMORY_API UPrimaryGameLayout : public UCommonUserWidget
{
	GENERATED_BODY()

public:

	template <typename ActivatableWidgetT = UMemoryActivatableWidget>
	TSharedPtr<FStreamableHandle> PushWidgetToLayerStackAsync(FGameplayTag LayerTag, bool bSuspendInputUntilComplete, TSoftClassPtr<UMemoryActivatableWidget> ActivatableWidgetClass)
	{
		return PushWidgetToLayerStackAsync<ActivatableWidgetT>(LayerTag, bSuspendInputUntilComplete, ActivatableWidgetClass, [](EAsyncWidgetLayerState, ActivatableWidgetT*) {});
	}

	template <typename ActivatableWidgetT = UMemoryActivatableWidget>
	TSharedPtr<FStreamableHandle> PushWidgetToLayerStackAsync(FGameplayTag LayerTag, bool bSuspendInputUntilComplete, TSoftClassPtr<UMemoryActivatableWidget> ActivatableWidgetClass, TFunction<void(EAsyncWidgetLayerState, ActivatableWidgetT*)> StateFunc)
	{
		static FName NAME_PushingWidgetToLayer("PushingWidgetToLayer");
		const FName SuspendInputToken = bSuspendInputUntilComplete ? UCommonUIExtension::SuspendInputForPlayer(GetOwningPlayer(), NAME_PushingWidgetToLayer) : NAME_None;

		FStreamableManager& StreamableManager = UAssetManager::Get().GetStreamableManager();
		TSharedPtr<FStreamableHandle> StreamingHandle = StreamableManager.RequestAsyncLoad(ActivatableWidgetClass.ToSoftObjectPath(), FStreamableDelegate::CreateWeakLambda(this,
			[this, LayerTag, ActivatableWidgetClass, StateFunc, SuspendInputToken]()
			{
				UCommonUIExtension::ResumeInputForPlayer(GetOwningPlayer(), SuspendInputToken);

				ActivatableWidgetT* Widget = PushWidgetToLayerStack<ActivatableWidgetT>
					(LayerTag, ActivatableWidgetClass.Get(), [StateFunc](ActivatableWidgetT& WidgetToInit)
						{
							StateFunc(EAsyncWidgetLayerState::Initialize, &WidgetToInit);
						}
					);

				StateFunc(EAsyncWidgetLayerState::AfterPush, Widget);
			})
		);

		StreamingHandle->BindCancelDelegate(FStreamableDelegate::CreateWeakLambda(this,
			[this, StateFunc, SuspendInputToken]()
			{
				UCommonUIExtension::ResumeInputForPlayer(GetOwningPlayer(), SuspendInputToken);

				StateFunc(EAsyncWidgetLayerState::Canceled, nullptr);
			})
		);

		return StreamingHandle;
	}

	template <typename ActivatableWidgetT = UMemoryActivatableWidget>
	ActivatableWidgetT* PushWidgetToLayerStack(FGameplayTag LayerTag, UClass* ActivatableWidgetClass)
	{
		return PushWidgetToLayerStack<ActivatableWidgetT>(LayerTag, ActivatableWidgetClass, [](ActivatableWidgetT&) {});
	}

	template <typename ActivatableWidgetT = UMemoryActivatableWidget>
	ActivatableWidgetT* PushWidgetToLayerStack(FGameplayTag LayerTag, UClass* ActivatableWidgetClass, TFunctionRef<void(ActivatableWidgetT&)> InstanceInitFunc)
	{
		if (UCommonActivatableWidgetContainerBase* Layer = GetLayerWidget(LayerTag))
		{
			return Layer->AddWidget<ActivatableWidgetT>(ActivatableWidgetClass, InstanceInitFunc);
		}

		return nullptr;
	}

	template <typename ActivatableWidgetT = UCommonActivatableWidget>
	TArray<ActivatableWidgetT*> GetWidgetsInLayer(FGameplayTag LayerTag)
	{
		if (UCommonActivatableWidgetContainerBase* Layer = GetLayerWidget(LayerTag))
		{
			return Layer->GetWidgetList();
		}

		return TArray<ActivatableWidgetT*>();
	}

	void FindAndRemoveWidgetFromLayer(FGameplayTag LayerTag, UMemoryActivatableWidget* ActivatableWidget);

	UCommonActivatableWidgetContainerBase* GetLayerWidget(FGameplayTag LayerTag);

protected:

	UFUNCTION(BlueprintCallable)
	void RegisterLayer(FGameplayTag LayerTag, UCommonActivatableWidgetContainerBase* LayerWidget);

	void OnWidgetStackTransitioning(UCommonActivatableWidgetContainerBase* Widget, bool bIsTransitioning);

private:

	TArray<FName> SuspendInputTokens;

	UPROPERTY()
	TMap<FGameplayTag, TObjectPtr<UCommonActivatableWidgetContainerBase>> Layers;
};