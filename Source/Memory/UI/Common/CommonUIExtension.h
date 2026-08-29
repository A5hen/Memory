// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameplayTagContainer.h"//
#include "CommonUIExtension.generated.h"

class UMemoryActivatableWidget;

/**
 * 
 */
UCLASS()
class MEMORY_API UCommonUIExtension : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "UI Extensions")
	static UMemoryActivatableWidget* PushContentToLayerForPlayer(
		APlayerController* PlayerController, FGameplayTag LayerTag, TSubclassOf<UMemoryActivatableWidget>WidgetClass);

	UFUNCTION(BlueprintCallable, Category = "UI Extensions")
	static UMemoryActivatableWidget* PushCoreWidgetToLayerForPlayer(
		APlayerController* PlayerController, FGameplayTag WidgetTag, FGameplayTag LayerTag);

	UFUNCTION(BlueprintCallable, Category = "UI Extensions")
	static void PushStreamedContentToLayerForPlayer(
		APlayerController* PlayerController, FGameplayTag LayerTag, TSoftClassPtr<UMemoryActivatableWidget> WidgetSoftClassPtr);

	UFUNCTION(BlueprintCallable, Category = "UI Extensions")
	static void PopContentFromLayer(APlayerController* PlayerController, FGameplayTag LayerTag, UMemoryActivatableWidget* ActivatableWidget);

	static FName SuspendInputForPlayer(APlayerController* PlayerController, FName SuspendReason);

	static void ResumeInputForPlayer(APlayerController* PlayerController, FName SuspendToken);

private:

	static int32 InputSuspensions;
};