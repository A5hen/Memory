// Fill out your copyright notice in the Description page of Project Settings.


#include "GraphWidget.h"
#include "Components/Overlay.h"//
#include "Components/CanvasPanel.h"//
#include "Memory/UI/CurveWidget.h"//

void UGraphWidget::ClearGraph()
{
}

void UGraphWidget::SetRenderTranslation(const FVector2D& NewTranslation)
{
	FWidgetTransform CurrentWidgetTranform = GetRenderTransform();
	CurrentWidgetTranform.Translation = NewTranslation;

	SetRenderTransform(CurrentWidgetTranform);
}

void UGraphWidget::ScaleGraph(float DeltaScale)
{
	if (DeltaScale < 0)
	{
		GraphScale = FMath::Max(0.5f, GraphScale - 0.1);
	}
	else
	{
		GraphScale = FMath::Min(1.f, GraphScale + 0.1);
	}

	FVector2D Scale = FVector2D(GraphScale, GraphScale);

	SetRenderScale(Scale);
}