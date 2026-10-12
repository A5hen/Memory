// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MemoryWidgetController.h"
#include "GameplayTagContainer.h"//
#include "Memory/MemoryType.h"//
#include "CognitionGraphWidgetController.generated.h"

struct FGeneratedBehavior;

DECLARE_MULTICAST_DELEGATE_OneParam(FUpdateCognitionMenu, const TGeneratedCharacterBehaviors&);
DECLARE_MULTICAST_DELEGATE_ThreeParams(FUpdateCognitionGraph, const FGameplayTag&, const FGeneratedBehavior&, bool);

/**
 * 
 */
UCLASS()
class MEMORY_API UCognitionGraphWidgetController : public UMemoryWidgetController
{
	GENERATED_BODY()

public:

	FUpdateCognitionMenu UpdateCognitionMenu;
	FUpdateCognitionGraph UpdateCognitionGraph;

	virtual void BroadcastInitialValues() override;

	virtual void BindCallBacksToDependencies() override;
};