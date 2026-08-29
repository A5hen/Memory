// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class MEMORY_API SInteractableText : public SCompoundWidget
{

public:

	SLATE_BEGIN_ARGS(SInteractableText){}

	SLATE_ARGUMENT(FText, InText)
	SLATE_ARGUMENT(FTextBlockStyle, InTextStyle)
	SLATE_ARGUMENT(UDataTable*, InRichTextStyleSet)
	SLATE_ARGUMENT(UObject*, InOwner)

	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

	~SInteractableText();

protected:

	FText Text;

	TSharedPtr<SButton> Button;
	TSharedPtr<STextBlock> TextBlock;

	FTextBlockStyle DefaultTextStyle;

	TWeakObjectPtr<UDataTable> RichTextStyleSet;

	TWeakObjectPtr<UObject> Owner;

	bool bExplanationDisplaying = false;
};