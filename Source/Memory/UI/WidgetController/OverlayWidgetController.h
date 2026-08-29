// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MemoryWidgetController.h"
#include "OverlayWidgetController.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class MEMORY_API UOverlayWidgetController : public UMemoryWidgetController
{
	GENERATED_BODY()
	
public:

	virtual void BroadcastInitialValues()override;

	virtual void BindCallBacksToDependencies()override;
};