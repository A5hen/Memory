// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/CancellableAsyncAction.h"
#include "GameplayTagContainer.h"//
#include "UObject/SoftObjectPtr.h"//
#include "AsyncAction_PushContentToLayerForPlayer.generated.h"

class APlayerController;
class UCommonActivatableWidget;
class UObject;
struct FFrame;
struct FStreamableHandle;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPushContentToLayerForPlayerAsyncDelegate, UCommonActivatableWidget*, UserWidget);

/**
 * 
 */
UCLASS(BlueprintType)
class MEMORY_API UAsyncAction_PushContentToLayerForPlayer : public UCancellableAsyncAction
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, BlueprintCosmetic, meta = (WorldContext = "WorldContextObject", BlueprintInternalUseOnly = "true"))
	static UAsyncAction_PushContentToLayerForPlayer* PushContentToLayerForPlayer(APlayerController* OwningPlayer, UPARAM(meta = (AllowAbstract = false)) TSoftClassPtr<UCommonActivatableWidget> WidgetClass, UPARAM(meta = (Categories = "UI.Layer")) FGameplayTag LayerName, bool bSuspendInputUntilComplete = true);

	virtual void Activate() override;

	virtual void Cancel() override;

public:

	UPROPERTY(BlueprintAssignable)
	FPushContentToLayerForPlayerAsyncDelegate BeforePush;

	UPROPERTY(BlueprintAssignable)
	FPushContentToLayerForPlayerAsyncDelegate AfterPush;

private:

	FGameplayTag LayerName;

	bool bSuspendInputUntilComplete = false;

	TWeakObjectPtr<APlayerController> OwningPlayerPtr;

	TSoftClassPtr<UCommonActivatableWidget> WidgetClass;

	TSharedPtr<FStreamableHandle> StreamingHandle;
};