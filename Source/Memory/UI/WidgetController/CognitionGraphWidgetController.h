// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MemoryWidgetController.h"
#include "GameplayTagContainer.h"//
#include "Memory/MemoryType.h"//
#include "CognitionGraphWidgetController.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FUpdateCognitionMenu, const TGeneratedCharacterBehaviorsType&);

/**
 * 
 */
UCLASS()
class MEMORY_API UCognitionGraphWidgetController : public UMemoryWidgetController
{
	GENERATED_BODY()

public:

	FUpdateCognitionMenu UpdateCognitionMenu;

	virtual void BroadcastInitialValues() override;

	virtual void BindCallBacksToDependencies() override;

	const FGeneratedBehaviorCognition* GetGeneratedBehaviorCognition(const FGameplayTag& CharacterTag, const FName& BehaviorDesc);
};