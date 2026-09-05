// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OptionWidget.generated.h"

class UTextBlock;

/**
 * 
 */
UCLASS()
class MEMORY_API UOptionWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	void SetOptionText(const FText& Option);

	void Select(bool bSelect);

protected:

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_Option;
};