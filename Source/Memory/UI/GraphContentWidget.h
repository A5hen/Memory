// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameplayTagContainer.h"//
#include "Memory/MemoryType.h"//
#include "GraphContentWidget.generated.h"

class UMemoryWidgetController;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBP_OnSelected);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnSelected, const FContentWidgetInfo&);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDisplayContentDelegate, const FContentWidgetInfo&, Info);

/**
 * 
 */
UCLASS()
class MEMORY_API UGraphContentWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	void DisplayContent();

	void NotifyController(bool bNotify) { bNotifyController = bNotify; }

protected:

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	void HandleMouseButtonDown();

	void HandleNotification();

public:

	FOnSelected OnSelected;

	FContentWidgetInfo ContentWidgetInfo;

	UPROPERTY(BlueprintAssignable, Category = "ContentDisplay")
	FDisplayContentDelegate DisplayContentDelegate;

protected:

	UPROPERTY(BlueprintAssignable, Category = "Selection")
	FBP_OnSelected BP_OnSelected;

	UPROPERTY()
	TObjectPtr<UMemoryWidgetController> WidgetController;

	bool bNotifyController = true;
};