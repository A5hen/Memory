// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OptionWidgetContainer.generated.h"

class UScrollBox;

/**
 * 
 */
UCLASS()
class MEMORY_API UOptionWidgetContainer : public UUserWidget
{
	GENERATED_BODY()

public:

	void AddOptionWidget(UUserWidget* InWidget);
	void ShowOptionWidget(const FText& Option, bool bShow);

protected:

	UPROPERTY(meta = (BindWidget))
	UScrollBox* ScrollBox_Root;
};