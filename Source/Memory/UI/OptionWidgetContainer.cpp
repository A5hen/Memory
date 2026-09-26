// Fill out your copyright notice in the Description page of Project Settings.


#include "OptionWidgetContainer.h"
#include "Components/ScrollBox.h"//
#include "Memory/UI/OptionWidget.h"//

void UOptionWidgetContainer::AddOptionWidget(int32 OptionIndex, UOptionWidget* OptionWidget)
{
	ScrollBox_Root->AddChild(OptionWidget);

	FOptionWidgetInfo OptionWidgetInfo;
	OptionWidgetInfo.OptionWidget = OptionWidget;

	OptionWidgetInfomation.Add(OptionIndex, OptionWidgetInfo);
}

void UOptionWidgetContainer::DisplayOptionWidget(int32 OptionIndex, bool bDisplay)
{
	if (FOptionWidgetInfo* Info = OptionWidgetInfomation.Find(OptionIndex))
	{
		if (bDisplay)
		{
			Info->OptionWidget->SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			Info->OptionWidget->SetVisibility(ESlateVisibility::Collapsed);
		}

		Info->bDisplayed = bDisplay;

		DisplayedOptionNum += bDisplay ? 1 : -1;
	}
}

bool UOptionWidgetContainer::IsOptionWidgetDisplayed(int32 OptionIndex) const
{
	if (const FOptionWidgetInfo* Info = OptionWidgetInfomation.Find(OptionIndex))
	{
		return Info->bDisplayed;
	}

	return false;
}

void UOptionWidgetContainer::SelectOptionWidget(int32 OptionIndex, bool bSelect)
{
	if (FOptionWidgetInfo* Info = OptionWidgetInfomation.Find(OptionIndex))
	{
		Info->OptionWidget->Select(bSelect);
		Info->bSelected = bSelect;
	}
}

bool UOptionWidgetContainer::IsOptionWidgetSelected(int32 OptionIndex) const
{
	if (const FOptionWidgetInfo* Info = OptionWidgetInfomation.Find(OptionIndex))
	{
		return Info->bSelected;
	}

	return false;
}

bool UOptionWidgetContainer::IsAnyOptionDisplayed() const
{
	return DisplayedOptionNum != 0;
}