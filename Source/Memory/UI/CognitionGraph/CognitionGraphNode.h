// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Memory/UI/GraphNodeWidget.h"
#include "GameplayTagContainer.h"//
#include "CognitionGraphNode.generated.h"

class UWidgetSwitcher;
class UButton;

class UGraphContentWidget;
struct FGeneratedBehaviorCognition;

/**
 * 
 */
UCLASS()
class MEMORY_API UCognitionGraphNode : public UGraphNodeWidget
{
	GENERATED_BODY()

public:

	void UpdateNode(const FGameplayTag& InCharactertag, const FName& InBehaviorDesc, const FGeneratedBehaviorCognition& GeneratedBehaviorCognition);

protected:

	UFUNCTION(BlueprintCallable, Category = "SwitchSourceEvent")
	void SwitchSourceEvent(bool bNext);

protected:

	UPROPERTY(meta = (BindWidget))
	UWidgetSwitcher* Switcher_Root;

	UPROPERTY(EditDefaultsOnly, Category = "Content")
	TSubclassOf<UGraphContentWidget> ContentClass_CharacterBehavior;

	FGameplayTagContainer SourceEvnetTags;

	int32 SwitcherIndex = 0;
};