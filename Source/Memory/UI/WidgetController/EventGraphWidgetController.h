// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MemoryWidgetController.h"
#include "Memory/MemoryType.h"//
#include "GameplayTagContainer.h"//
#include "EventGraphWidgetController.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FUpdateEventMenu, const TExperiencedEventInfomation_AllStage&)
DECLARE_MULTICAST_DELEGATE_ThreeParams(FUpdateEventGraph, const FGameplayTag&, const FExperiencedEventInfomation&, bool);

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class MEMORY_API UEventGraphWidgetController : public UMemoryWidgetController
{
	GENERATED_BODY()
	
public:

	FUpdateEventMenu UpdateEventMenu;
	FUpdateEventGraph UpdateEventGraph;

	virtual void BroadcastInitialValues() override;

	virtual void BindCallBacksToDependencies() override;
};