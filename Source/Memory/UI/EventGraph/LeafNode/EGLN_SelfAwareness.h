// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameplayTagContainer.h"//
#include "EGLN_SelfAwareness.generated.h"

class UScrollBox;

class UGraphContentWidget;

/**
 * 
 */
UCLASS()
class MEMORY_API UEGLN_SelfAwareness : public UUserWidget
{
	GENERATED_BODY()

public:

	void UpdateLeafNode(const FGameplayTag& EventTag, const FGameplayTagContainer& GeneratedSelfAwareness);

protected:

	UPROPERTY(meta = (BindWidget))
	UScrollBox* ScrollBox_SelfAwareness;
	
	UPROPERTY(EditDefaultsOnly, Category = "Overview")
	TSubclassOf<UGraphContentWidget> OverviewClass_SelfAwareness;
};