// Fill out your copyright notice in the Description page of Project Settings.


#include "SInteractableText.h"
#include "SlateOptMacros.h"
#include "Components/RichTextBlock.h"//
#include "Kismet/GameplayStatics.h"//
#include "MemoryRichText.h"//
#include "Memory/UI/Common/CommonUIExtension.h"//

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
						const FRichTextStyleRow* HoveredStyle = RichTextStyleSet->FindRow<FRichTextStyleRow>(FName("E_Hovered"), TEXT("Can't find row: E_Hovered"));
						if (HoveredStyle)
						{
							TextBlock->SetTextStyle(&HoveredStyle->TextStyle);
						}
					}
				}
			)
			.OnUnhovered_Lambda
			([this]()
				{
					if (RichTextStyleSet.IsValid())
					{
						const FRichTextStyleRow* UnhoveredStyle = RichTextStyleSet->FindRow<FRichTextStyleRow>(FName("E_Unhovered"), TEXT("Can't find row: E_Unhovered"));
						if (UnhoveredStyle)
						{
							TextBlock->SetTextStyle(&UnhoveredStyle->TextStyle);
						}
					}
				}
			)
			.OnClicked_Lambda
			([this]()
				{
					if (Owner.IsValid())
					{
						if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(Owner.Get(), 0))
						{
							UCommonUIExtension::PushExplanationToLayerForPlayer(PlayerController);
						}
					}
					return FReply::Handled();
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
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION