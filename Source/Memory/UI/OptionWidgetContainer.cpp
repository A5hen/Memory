// Fill out your copyright notice in the Description page of Project Settings.


#include "OptionWidgetContainer.h"
#include "Components/WrapBox.h"//

void UOptionWidgetContainer::AddOptionWidget(UUserWidget* InWidget)
{
	WrapBox_Root->AddChildToWrapBox(InWidget);
}