// Fill out your copyright notice in the Description page of Project Settings.


#include "CurveWidget.h"

void UCurveWidget::UpdateCurveSpawnInfo(const FGameplayTag& Tag, const FVector2D& Position, const TArray<FVector2D>& RelativePositionsToConnect, const TMap<FVector2D, TArray<FVector2D>>& PositionsToConnect)
{
	FCurveSpawnInfo NewInfo;
	NewInfo.Position = Position;
	NewInfo.RelativePositionsToConnect = RelativePositionsToConnect;
	NewInfo.PositionsToConnect = PositionsToConnect;

	CurveSpawnInfomation.Emplace(Tag, NewInfo);
}

int32 UCurveWidget::NativePaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
	FVector2D Center = AllottedGeometry.GetLocalSize() / 2;

	for (const auto& Pair : CurveSpawnInfomation)
	{
		for (const auto& Positions : Pair.Value.PositionsToConnect)
		{
			if (Positions.Value.Num() == 0)continue;

			FVector2D ActualStart = Positions.Key + Center + CurveOffset;

			for (const FVector2D& End : Positions.Value)
			{
				FVector2D ActualEnd = End + Center + CurveOffset;

				int32 ControlPonitX = ActualEnd.X + (ActualStart.X - ActualEnd.X) / 2;

				FSlateDrawElement::MakeCubicBezierSpline(OutDrawElements, LayerId, AllottedGeometry.ToPaintGeometry(),
					ActualStart, FVector2D(ControlPonitX, ActualStart.Y),
					FVector2D(ControlPonitX, ActualEnd.Y), ActualEnd, 4.f);
			}
		}

		FVector2D ActualNodePosition = Pair.Value.Position + Center + CurveOffset;

		for (const FVector2D& RelativePosition : Pair.Value.RelativePositionsToConnect)
		{
			if (RelativePosition == FVector2D())continue;

			FVector2D ActualPositionToConnect = ActualNodePosition + RelativePosition;

			int32 ControlPonitX = ActualPositionToConnect.X + (ActualNodePosition.X - ActualPositionToConnect.X) / 2;

			FSlateDrawElement::MakeCubicBezierSpline(OutDrawElements, LayerId + 1, AllottedGeometry.ToPaintGeometry(),
				ActualNodePosition, FVector2D(ControlPonitX, ActualNodePosition.Y),
				FVector2D(ControlPonitX, ActualPositionToConnect.Y), ActualPositionToConnect, 4.f, ESlateDrawEffect::None, FLinearColor::Gray);
		}
	}

	return LayerId + 2;
}