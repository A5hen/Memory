// Fill out your copyright notice in the Description page of Project Settings.


#include "OptionWidgetContainer.h"
#include "Components/ScrollBox.h"//
#include "Memory/UI/OptionWidget.h"//

void UOptionWidgetContainer::AddOptionWidget(UUserWidget* InWidget)
{
	ScrollBox_Root->AddChild(InWidget);
}

void UOptionWidgetContainer::ShowOptionWidget(const FText& Option, bool bShow)
{
	for (UWidget* Widget : ScrollBox_Root->GetAllChildren())
	{
		if (UOptionWidget* OptionWidget = Cast<UOptionWidget>(Widget))
		{
			if (OptionWidget->GetOptionText().IdenticalTo(Option))
			{
				if (bShow)
				{
					OptionWidget->SetVisibility(ESlateVisibility::Visible);
				}
				else
				{
					OptionWidget->SetVisibility(ESlateVisibility::Collapsed);
				}

				return;
			}
		}
	}
}