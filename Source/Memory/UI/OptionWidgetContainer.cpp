// Fill out your copyright notice in the Description page of Project Settings.


#include "OptionWidgetContainer.h"
#include "Components/ScrollBox.h"//
#include "Memory/UI/OptionWidget.h"//

void UOptionWidgetContainer::AddOptionWidget(const FName& ID, UOptionWidget* OptionWidget)
{
	ScrollBox_Root->AddChild(OptionWidget);

	FOptionWidgetInfo OptionWidgetInfo;
	OptionWidgetInfo.OptionWidget = OptionWidget;

	OptionWidgetInfomation.Add(ID, OptionWidgetInfo);
}

void UOptionWidgetContainer::DisplayOptionWidget(const FName& ID, bool bDisplay)
{
	if (OptionWidgetInfomation.Find(ID))
	{
		FOptionWidgetInfo& Info = OptionWidgetInfomation[ID];

		if (bDisplay)
		{
			Info.OptionWidget->SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			Info.OptionWidget->SetVisibility(ESlateVisibility::Collapsed);
		}

		Info.bDisplayed = bDisplay;

		DisplayedOptionNum += bDisplay ? 1 : -1;
	}
}

bool UOptionWidgetContainer::IsOptionWidgetDisplayed(const FName& ID) const
{
	if (OptionWidgetInfomation.Find(ID))
	{
		const FOptionWidgetInfo& Info = OptionWidgetInfomation[ID];

		return Info.bDisplayed;
	}

	return false;
}

void UOptionWidgetContainer::SelectOptionWidget(const FName& ID, bool bSelect)
{
	if (OptionWidgetInfomation.Find(ID))
	{
		FOptionWidgetInfo& Info = OptionWidgetInfomation[ID];

		Info.OptionWidget->Select(bSelect);
		Info.bSelected = bSelect;
	}
}

bool UOptionWidgetContainer::IsOptionWidgetSelected(const FName& ID) const
{
	if (OptionWidgetInfomation.Find(ID))
	{
		const FOptionWidgetInfo& Info = OptionWidgetInfomation[ID];

		return Info.bSelected;
	}

	return false;
}

bool UOptionWidgetContainer::IsAnyOptionDisplayed() const
{
	return DisplayedOptionNum != 0;
}