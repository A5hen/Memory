// Fill out your copyright notice in the Description page of Project Settings.


#include "SInteractableText.h"
#include "SlateOptMacros.h"
#include "Components/RichTextBlock.h"//
#include "MemoryRichText.h"//
#include "Memory/UI/Explanation/ExplanationInterface.h"//

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
void SInteractableText::Construct(const FArguments& InArgs)
{
	Text = InArgs._InText;

	DefaultTextStyle = InArgs._InTextStyle;
	RichTextStyleSet = InArgs._InRichTextStyleSet;
	Owner = InArgs._InOwner;

	ChildSlot
	[
		SAssignNew(Button, SButton)
			.ButtonStyle(FCoreStyle::Get(), "NoBorder")
			.OnHovered_Lambda
			([this]()
				{
					if(RichTextStyleSet.IsValid())
					{
						const FRichTextStyleRow* HoveredTipStyle = RichTextStyleSet->FindRow<FRichTextStyleRow>(FName("E_Hovered"), TEXT("Can't find row: E_Hovered"));
						if (HoveredTipStyle)
						{
							TextBlock->SetTextStyle(&HoveredTipStyle->TextStyle);
						}
					}

					if(Owner.IsValid())
					{
						if (UMemoryRichText* MemoryRichText = Cast<UMemoryRichText>(Owner.Get()))
						{
							if (IExplanationInterface* EI = Cast<IExplanationInterface>(MemoryRichText->GetOwner()))
							{
								EI->ShowExplanation(true, Text);
								bExplanationDisplaying = true;
							}
						}
					}
				}
			)
			.OnUnhovered_Lambda
			([this]()
				{
					if (RichTextStyleSet.IsValid())
					{
						const FRichTextStyleRow* UnhoveredTipStyle = RichTextStyleSet->FindRow<FRichTextStyleRow>(FName("E_Unhovered"), TEXT("Can't find row: E_Unhovered"));
						if (UnhoveredTipStyle)
						{
							TextBlock->SetTextStyle(&UnhoveredTipStyle->TextStyle);
						}
					}

					if (Owner.IsValid())
					{
						if (UMemoryRichText* MemoryRichText = Cast<UMemoryRichText>(Owner.Get()))
						{
							if (IExplanationInterface* EI = Cast<IExplanationInterface>(MemoryRichText->GetOwner()))
							{
								EI->ShowExplanation(false, Text);
								bExplanationDisplaying = false;
							}
						}
					}
				}
			)
			.Content()
			[
				SAssignNew(TextBlock, STextBlock)
					.Text(Text)
					.TextStyle(&DefaultTextStyle)
			]
	];
	
}

SInteractableText::~SInteractableText()
{
	if (bExplanationDisplaying)
	{
		if (Owner.IsValid())
		{
			if (UMemoryRichText* MemoryRichText = Cast<UMemoryRichText>(Owner.Get()))
			{
				if (IExplanationInterface* EI = Cast<IExplanationInterface>(MemoryRichText->GetOwner()))
				{
					EI->ShowExplanation(true, Text);
				}
			}
		}
	}
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION