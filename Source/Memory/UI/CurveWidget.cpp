// Fill out your copyright notice in the Description page of Project Settings.


#include "CurveWidget.h"

void UCurveWidget::UpdateCurveSpawnInfo(const FGameplayTag& Tag,
	const FVector2D& Position,
	const TMap<FVector2D, FTargetPoint>& StartToEnd)
{
	FCurveSpawnInfo NewInfo;
	NewInfo.Position = Position;
	NewInfo.StartToEnd = StartToEnd;

	CurveSpawnInfomation.Emplace(Tag, NewInfo);
}

int32 UCurveWidget::NativePaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
	FVector2D Center = AllottedGeometry.GetLocalSize() / 2;

	for (const auto& Pair : CurveSpawnInfomation)
	{
		for (const auto& Pair1 : Pair.Value.StartToEnd)
		{
			FVector2D ActualStart = Pair1.Key + Center;
			FVector2D ActualEnd = Pair1.Value.Position + Center;

			FVector2D Mid1 = (ActualStart + ActualEnd) / 2;
			FVector2D Mid2 = (Pair.Value.Position - Pair1.Value.WidgetPosition) / 2 + Center;

			float Length = (Mid1 - Mid2).Length();
			FVector2D PoleVector = (Mid1 - Mid2).GetSafeNormal();

			FVector2D ControlPonit = Mid1 + PoleVector * Length;

			FSlateDrawElement::MakeCubicBezierSpline(OutDrawElements, LayerId, AllottedGeometry.ToPaintGeometry(),
				ActualStart, ControlPonit,
				ControlPonit, ActualEnd, 4.f);
		}
	}

	return LayerId + 1;
}