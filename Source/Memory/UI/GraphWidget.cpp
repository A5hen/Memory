// Fill out your copyright notice in the Description page of Project Settings.


#include "GraphWidget.h"
#include "Components/CanvasPanel.h"//
#include "Memory/UI/CurveWidget.h"//

void UGraphWidget::SetWidgetController(UMemoryWidgetController* InWidgetController)
{
	WidgetController = InWidgetController;
}

void UGraphWidget::ClearGraph()
{
}

void UGraphWidget::UnbindCallBacks()
{
}

void UGraphWidget::SetRelativeTransform(const FWidgetTransform& InTransform)
{
	RelativeTransform = InTransform;

	CanvasPanel_Root->SetRenderTransform(InTransform);

	CurveWidget->SetCurveOffset(InTransform.Translation);
}