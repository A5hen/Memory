// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MemoryActivatableWidget.h"
#include "CharacterCognitionMenu.generated.h"

class UScrollBox;

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

	virtual void OnContentSelected(const FContentWidgetInfo& ContentWidgetInfo) override;

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void ShowDetail();
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void HideDetail();

	void UpdateCharacterSwitcher(const FGameplayTagContainer& CharacterTags);
	void OnCharacterSelected(const FContentWidgetInfo& ContentWidgetInfo);

protected:

	UPROPERTY(meta = (BindWidget))
	UScrollBox* ScrollBox_Character;

	FGameplayTagContainer SelectableCharacterTags;

	UPROPERTY(meta = (BindWidget))
	UCharacterCognitionGraph* CharacterCognitionGraph;

	UPROPERTY(meta = (BindWidget))
	UBehaviorCognitionDetail* BehaviorCognitionDetail;

	UPROPERTY(EditDefaultsOnly, Category = "Overview")
	TSubclassOf<UGraphContentWidget> OverviewClass_Character;
	
	bool bMouseDown = false;

	FVector2D MousePosition;
	FVector2D MousePositionLastFrame;

	FVector2D GraphOffset;
};