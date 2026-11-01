// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameplayTagContainer.h"
#include "CurveWidget.generated.h"

class UOverlay;

struct FTargetPoint
{
	FVector2D Position;
	
	FVector2D WidgetPosition;
};

struct FCurveSpawnInfo
{
	FVector2D Position;

	TMap<FVector2D, FTargetPoint> StartToEnd;
};

/**
 * 
 */
UCLASS()
class MEMORY_API UCurveWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	void UpdateCurveSpawnInfo(const FGameplayTag& Tag,
		const FVector2D& Position,
		const TMap<FVector2D, FTargetPoint>& PositionsToConnect);

	void ClearCurveSpawnInfomation() { CurveSpawnInfomation.Empty(); }

protected:

	virtual int32 NativePaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;

protected:

	UPROPERTY(meta = (BindWidget))
	UOverlay* Overlay_Root;

	TMap<FGameplayTag, FCurveSpawnInfo>CurveSpawnInfomation;
};