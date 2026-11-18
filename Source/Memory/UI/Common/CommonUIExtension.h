// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameplayTagContainer.h"//
#include "CommonUIExtension.generated.h"

class UCommonActivatableWidget;

class UPrimaryGameLayout;

/**
 * 
 */
UCLASS()
class MEMORY_API UCommonUIExtension : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "UI Extensions")
	static UPrimaryGameLayout* GetPrimaryGameLayout(APlayerController* PlayerController);

	UFUNCTION(BlueprintCallable, Category = "UI Extensions")
	static UCommonActivatableWidget *PushContentToLayerForPlayer(
		APlayerController* PlayerController, FGameplayTag LayerTag, TSubclassOf<class UCommonActivatableWidget> WidgetClass);

	UFUNCTION(BlueprintCallable, Category = "UI Extensions")
	static void PushStreamedContentToLayerForPlayer(
		APlayerController* PlayerController, FGameplayTag LayerTag, TSoftClassPtr<class UCommonActivatableWidget> WidgetSoftClassPtr);

	UFUNCTION(BlueprintCallable, Category = "UI Extensions")
	static UCommonActivatableWidget* PushExplanationToLayerForPlayer(APlayerController* PlayerController);

	UFUNCTION(BlueprintCallable, Category = "UI Extensions")
	static UWidget* SwitchToCoreWidgetForPlayer(APlayerController* PlayerController, FGameplayTag CoreWidgetTag);

	UFUNCTION(BlueprintCallable, Category = "UI Extensions")
	static void PopContentFromLayer(APlayerController* PlayerController, FGameplayTag LayerTag, class UCommonActivatableWidget* ActivatableWidget);

	static FName SuspendInputForPlayer(APlayerController* PlayerController, FName SuspendReason);

	static void ResumeInputForPlayer(APlayerController* PlayerController, FName SuspendToken);

private:

	static int32 InputSuspensions;
};