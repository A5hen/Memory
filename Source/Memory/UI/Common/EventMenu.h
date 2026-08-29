// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MemoryActivatableWidget.h"
#include "EventMenu.generated.h"

class USizeBox;
class UCommonButtonBase;

class UEventGraph;
class UEventDetail;

struct FContentWidgetInfo;

/**
 * 
 */
UCLASS()
class MEMORY_API UEventMenu : public UMemoryActivatableWidget
{
	GENERATED_BODY()
	
public:

	virtual void SetWidgetController(UMemoryWidgetController* InWidgetController) override;

protected:

	virtual void NativeOnInitialized() override;

	virtual void NativeOnActivated() override;
	virtual void NativeOnDeactivated() override;

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual FReply NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual FReply NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual FReply NativeOnMouseWheel(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	virtual void OnContentSelected(const FContentWidgetInfo& ContentWidgetInfo) override;

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void ShowDetail();
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void HideDetail();

	void UpdateEventStageSwitcher(EEventStage CurrentEventStage);
	void OnEventStageSelected(EEventStage TargetStage);

	void StartGraphScale();
	void EndGraphScale();

protected:

	UPROPERTY(meta = (BindWidget))
	UEventGraph* EventGraph;

	UPROPERTY(meta = (BindWidget))
	UEventDetail* EventDetail;

	UPROPERTY(meta = (BindWidget))
	UCommonButtonBase* CoreWidgetJumpButton;

	UPROPERTY(EditDefaultsOnly, Category = "ScaleTag")
	FGameplayTag ScaleTag;

	bool bMouseDown = false;

	FVector2D MousePosition;
	FVector2D MousePositionLastFrame;

	FVector2D GraphOffset;

	float GraphScale = 1.f;
	bool bScalable = false;
};