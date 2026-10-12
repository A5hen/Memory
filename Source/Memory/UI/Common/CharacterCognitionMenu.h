// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MemoryActivatableWidget.h"
#include "CharacterCognitionMenu.generated.h"

class UScrollBox;
class UWidgetSwitcher;

class UCharacterCognitionGraph;
class UBehaviorCognitionDetail;

class UGraphContentWidget;
struct FContentWidgetInfo;

/**
 * 
 */
UCLASS()
class MEMORY_API UCharacterCognitionMenu : public UMemoryActivatableWidget
{
	GENERATED_BODY()

public:

	virtual void SetWidgetController(UMemoryWidgetController* InWidgetController) override;

	UFUNCTION(BlueprintCallable)
	void TestJumpFunction();

protected:

	virtual void NativeOnActivated() override;
	virtual void NativeOnDeactivated() override;

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual FReply NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual FReply NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	virtual void HandleCoreWidgetJump(const FContentWidgetInfo& ContentWidgetInfo) override;

	virtual void OnContentSelected(const FContentWidgetInfo& ContentWidgetInfo) override;

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void ShowDetail();
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void HideDetail();

	void UpdateCognitionMenu(const TMap<FGameplayTag, FGeneratedBehavior>& GeneratedCharacterBehaviors);
	void GenerateCognitionGraph(const FGameplayTag& CharacterTag, const FGeneratedBehavior& GeneratedBehavior);
	void UpdateCognitionGraph(const FGameplayTag& CharacterTag,	const FGeneratedBehavior& GeneratedBehavior, bool bNewCharacter);

	void UpdateCharacterSwitcher(const FGameplayTagContainer& NewSelectableCharacters);
	void OnCharacterSelected(const FContentWidgetInfo& ContentWidgetInfo);

protected:

	UPROPERTY(meta = (BindWidget))
	UScrollBox* ScrollBox_Character;

	FGameplayTagContainer SelectableCharacters;

	/*CharacterCognitionGraph*/
	UPROPERTY(EditDefaultsOnly, Category = "CharacterCognitionGraph")
	TSubclassOf<UCharacterCognitionGraph> CharacterCognitionGraphClass;

	UPROPERTY(meta = (BindWidget))
	UWidgetSwitcher* GraphSwitcher;

	UPROPERTY()
	TMap<FGameplayTag, TObjectPtr<UCharacterCognitionGraph>> GeneratedCharacterCognitionGraphs;

	UPROPERTY(EditDefaultsOnly, Category = "CharacterCognitionGraph")
	FGameplayTag CurrentCharacter;

	UPROPERTY()
	TObjectPtr<UCharacterCognitionGraph> CurrentCharacterCognitionGraph;
	/*CharacterCognitionGraph*/

	UPROPERTY(meta = (BindWidget))
	UBehaviorCognitionDetail* BehaviorCognitionDetail;

	UPROPERTY(EditDefaultsOnly, Category = "Overview_Character")
	TSubclassOf<UGraphContentWidget> OverviewClass_Character;
	
	bool bMouseDown = false;

	FVector2D MouseStartPosition;
	FVector2D MouseCurrentPosition;
	FWidgetTransform GraphStartTransform;

	bool bFirstUpdate = true;
};