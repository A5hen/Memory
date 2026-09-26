// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OptionWidgetContainer.generated.h"

class UScrollBox;

class UOptionWidget;

USTRUCT()
struct FOptionWidgetInfo
{
	GENERATED_BODY()

	UPROPERTY()
	UOptionWidget* OptionWidget = nullptr;

	bool bSelected = false;

	bool bDisplayed = false;
};

/**
 * 
 */
UCLASS()
class MEMORY_API UOptionWidgetContainer : public UUserWidget
{
	GENERATED_BODY()

public:

	void AddOptionWidget(int32 OptionIndex, UOptionWidget* OptionWidget);

	void DisplayOptionWidget(int32 OptionIndex, bool bDisplay);
	bool IsOptionWidgetDisplayed(int32 OptionIndex) const;

	void SelectOptionWidget(int32 OptionIndex, bool bSelect);
	bool IsOptionWidgetSelected(int32 OptionIndex) const;

	bool IsAnyOptionDisplayed() const;

protected:

	UPROPERTY()
	TMap<int32, FOptionWidgetInfo> OptionWidgetInfomation;

	UPROPERTY(meta = (BindWidget))
	UScrollBox* ScrollBox_Root;

	int32 DisplayedOptionNum = 0;
};