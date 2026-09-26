// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EventDetail.generated.h"

class UGraphContentWidget;
struct FContentWidgetInfo;

/**
 * 
 */
UCLASS()
class MEMORY_API UEventDetail : public UUserWidget
{
	GENERATED_BODY()

public:

	void UpdateDetail(const FContentWidgetInfo& ContentWidgetInfo);
};