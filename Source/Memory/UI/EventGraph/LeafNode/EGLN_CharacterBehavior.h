// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameplayTagContainer.h"//
#include "EGLN_CharacterBehavior.generated.h"

class UScrollBox;

class UGraphContentWidget;
struct FContentWidgetInfo;

/**
 * 
 */
UCLASS()
class MEMORY_API UEGLN_CharacterBehavior : public UUserWidget
{
	GENERATED_BODY()
	
public:

	void UpdateLeafNode(const FGameplayTag& EventTag, const TMap<FGameplayTag, TArray<FName>>& CharacterBehavior);

protected:

	void OnCharacterSelected(const FContentWidgetInfo& ContentWidgetInfo);

protected:

	UPROPERTY(meta = (BindWidget))
	UScrollBox* ScrollBox_Character;

	UPROPERTY(meta = (BindWidget))
	UScrollBox* ScrollBox_CharacterBehavior;

	UPROPERTY(EditDefaultsOnly, Category = "Overview")
	TSubclassOf<UGraphContentWidget> OverviewClass_Character;

	UPROPERTY(EditDefaultsOnly, Category = "Overview")
	TSubclassOf<UGraphContentWidget> OverviewClass_CharacterBehavior;

	TMap<FGameplayTag, TArray<FName>> GeneratedCharacterBehavior;

	FGameplayTag SelectedCharacterTag;
};