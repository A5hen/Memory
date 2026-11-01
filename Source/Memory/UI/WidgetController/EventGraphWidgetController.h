// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MemoryWidgetController.h"
#include "GameplayTagContainer.h"//
#include "Memory/MemoryType.h"//
#include "EventGraphWidgetController.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FUpdateEventMenu, const TExperiencedEventInfomationType_AllStage&)

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class MEMORY_API UEventGraphWidgetController : public UMemoryWidgetController
{
	GENERATED_BODY()
	
public:

	FUpdateEventMenu UpdateEventMenu;

	virtual void BroadcastInitialValues() override;

	virtual void BindCallBacksToDependencies() override;
};