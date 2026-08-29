// Fill out your copyright notice in the Description page of Project Settings.


#include "OptionWidget.h"
#include "Components/TextBlock.h"//

void UOptionWidget::SetOptionInfo(const FText& NewOption)
{
	if (!NewOption.IsEmpty())
	{
		Option->SetText(NewOption);
	}
}