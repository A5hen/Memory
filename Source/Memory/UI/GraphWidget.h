// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GraphWidget.generated.h"

class UOverlay;
class UCanvasPanel;

class UCurveWidget;
class UMemoryWidgetController;

/**
 * 
 */
UCLASS()
class MEMORY_API UGraphWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual void SetWidgetController(UMemoryWidgetController* InWidgetController);
	virtual void ClearGraph();
	virtual void UnbindCallBacks();

	const FWidgetTransform& GetRelativeTransform() { return RelativeTransform; }
	void SetRelativeTransform(const FWidgetTransform& InTransform);

protected:

	UPROPERTY(meta = (BindWidget))
	UOverlay* Overlay_Root;

	UPROPERTY(meta = (BindWidget))
	UCanvasPanel* CanvasPanel_Root;

	UPROPERTY(meta = (BindWidget))
	UCurveWidget* CurveWidget;

	UPROPERTY()
	TObjectPtr<UMemoryWidgetController>WidgetController;

	FWidgetTransform RelativeTransform;
};