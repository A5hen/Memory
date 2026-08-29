// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OptionWidgetContainer.generated.h"

class UWrapBox;

/**
 * 
 */
UCLASS()
class MEMORY_API UOptionWidgetContainer : public UUserWidget
{
	GENERATED_BODY()

public:

	void AddOptionWidget(UUserWidget* InWidget);

protected:

	UPROPERTY(meta = (BindWidget))
	UWrapBox* WrapBox_Root;
};