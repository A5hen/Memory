// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MemoryWidgetController.h"
#include "GameplayTagContainer.h"//
#include "CognitionGraphWidgetController.generated.h"

struct FBehaviorCognitionInfomation;

DECLARE_MULTICAST_DELEGATE_OneParam(FUpdateCognitionGraph, const FBehaviorCognitionInfomation&);

/**
 * 
 */
UCLASS()
class MEMORY_API UCognitionGraphWidgetController : public UMemoryWidgetController
{
	GENERATED_BODY()

public:

	FUpdateCognitionGraph UpdateCognitionGraph;

	virtual void BroadcastInitialValues() override;

	virtual void BindCallBacksToDependencies() override;

	const FGameplayTag& GetSelectedCharacter() const { return SelectedCharacter; }
	const FGameplayTagContainer& GetSelectableCharacters() const { return SelectableCharacters; }
	
protected:

	UPROPERTY(EditDefaultsOnly, Category = "Character")
	FGameplayTagContainer SelectableCharacters;

	UPROPERTY(EditDefaultsOnly, Category = "Character")
	FGameplayTag SelectedCharacter;
};