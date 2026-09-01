// Fill out your copyright notice in the Description page of Project Settings.


#include "OptionWidget.h"
#include "Components/TextBlock.h"//

void UOptionWidget::SetOptionText(const FText& Option)
{
	if (!Option.IsEmpty())
	{
		Text_Option->SetText(Option);
		OptionText = Option;
	}
}

const FText& UOptionWidget::GetOptionText() const
{
	return OptionText;
}