// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameplayTagContainer.h"
#include "CurveWidget.generated.h"

class UOverlay;

struct FCurveSpawnInfo
{
	FVector2D Position;

	TArray<FVector2D> RelativePositionsToConnect;

	TMap<FVector2D, TArray<FVector2D>> PositionsToConnect;
};

/**
 * 
 */
UCLASS()
class MEMORY_API UCurveWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	void UpdateCurveSpawnInfo(const FGameplayTag& Tag, const FVector2D& Position, const TArray<FVector2D>& RelativePositionsToConnect, const TMap<FVector2D, TArray<FVector2D>>& PositionsToConnect);
	void SetCurveOffset(const FVector2D& Offset) { CurveOffset = Offset; }

	void ClearCurveSpawnInfomation() { CurveSpawnInfomation.Empty(); }

protected:

	virtual int32 NativePaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;

protected:

	UPROPERTY(meta = (BindWidget))
	UOverlay* Overlay_Root;

	TMap<FGameplayTag, FCurveSpawnInfo>CurveSpawnInfomation;

	FVector2D CurveOffset;
};