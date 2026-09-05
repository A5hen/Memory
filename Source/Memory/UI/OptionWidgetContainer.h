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

	void AddOptionWidget(const FName& ID, UOptionWidget* OptionWidget);

	void DisplayOptionWidget(const FName& ID, bool bDisplay);
	bool IsOptionWidgetDisplayed(const FName& ID) const;

	void SelectOptionWidget(const FName& ID, bool bSelect);
	bool IsOptionWidgetSelected(const FName& ID) const;

	bool IsAnyOptionDisplayed() const;

protected:

	UPROPERTY()
	TMap<FName, FOptionWidgetInfo> OptionWidgetInfomation;

	UPROPERTY(meta = (BindWidget))
	UScrollBox* ScrollBox_Root;

	int32 DisplayedOptionNum = 0;
};