// Fill out your copyright notice in the Description page of Project Settings.


#include "Memory/UI/RichText/MemoryRichTextDecorator.h"
#include "UObject/SoftObjectPtr.h"
#include "Rendering/DrawElements.h"
#include "Framework/Text/SlateTextRun.h"
#include "Framework/Text/SlateWidgetRun.h"
#include "Framework/Application/SlateApplication.h"
#include "Fonts/FontMeasure.h"
#include "Components/RichTextBlock.h"
#include "Widgets/Input/Sbutton.h"//
#include "Widgets/Text/STextBlock.h"//
#include "SInteractableText.h"//

FHoverDecorator::FHoverDecorator(URichTextBlock* InOwner)
	: Owner(InOwner)
{
}

TSharedRef<ISlateRun> FHoverDecorator::Create(const TSharedRef<class FTextLayout>& TextLayout, const FTextRunParseResults& RunParseResult, const FString& OriginalText, const TSharedRef< FString >& InOutModelText, const ISlateStyle* Style)
{
	FTextRange ModelRange;
	ModelRange.BeginIndex = InOutModelText->Len();

	FTextRunInfo RunInfo(RunParseResult.Name, FText::FromString(OriginalText.Mid(RunParseResult.ContentRange.BeginIndex, RunParseResult.ContentRange.EndIndex - RunParseResult.ContentRange.BeginIndex)));
	for (const TPair<FString, FTextRange>& Pair : RunParseResult.MetaData)
	{
		RunInfo.MetaData.Add(Pair.Key, OriginalText.Mid(Pair.Value.BeginIndex, Pair.Value.EndIndex - Pair.Value.BeginIndex));
	}

	const FTextBlockStyle& TextStyle = Owner->GetCurrentDefaultTextStyle();

	UDataTable* TextStyleSet = Owner->GetTextStyleSet();
	const FRichTextStyleRow* UnhoveredTipStyle = TextStyleSet->FindRow<FRichTextStyleRow>(FName("E_Unhovered"), TEXT("Can't find row: E_Unhovered"));

	TSharedPtr<ISlateRun> SlateRun;

	TSharedPtr<SWidget> DecoratorWidget;
	if (UnhoveredTipStyle)
	{
		DecoratorWidget = CreateDecoratorWidget(RunInfo, UnhoveredTipStyle->TextStyle);
	}
	else
	{
		DecoratorWidget = CreateDecoratorWidget(RunInfo, TextStyle);
	}


	if (DecoratorWidget.IsValid())
	{
		*InOutModelText += TEXT('\u200B'); // Zero-Width Breaking Space
		ModelRange.EndIndex = InOutModelText->Len();

		// Calculate the baseline of the text within the owning rich text
		// Requested on demand as the font may not be loaded right now
		const FSlateFontInfo Font = TextStyle.Font;
		const float ShadowOffsetY = FMath::Min(0.0f, TextStyle.ShadowOffset.Y);

		TAttribute<int16> GetBaseline = TAttribute<int16>::CreateLambda([Font, ShadowOffsetY]()
			{
				const TSharedRef<FSlateFontMeasure> FontMeasure = FSlateApplication::Get().GetRenderer()->GetFontMeasureService();
				return FontMeasure->GetBaseline(Font) - ShadowOffsetY;
			});

		FSlateWidgetRun::FWidgetRunInfo WidgetRunInfo(DecoratorWidget.ToSharedRef(), GetBaseline);
		SlateRun = FSlateWidgetRun::Create(TextLayout, RunInfo, InOutModelText, WidgetRunInfo, ModelRange);
	}
	else
	{
		// Assume there's a text handler if widget is empty, if there isn't one it will just display an empty string
		FTextBlockStyle TempStyle = TextStyle;
		CreateDecoratorText(RunInfo, TempStyle, *InOutModelText);

		ModelRange.EndIndex = InOutModelText->Len();
		SlateRun = FSlateTextRun::Create(RunInfo, InOutModelText, TempStyle, ModelRange);
	}

	return SlateRun.ToSharedRef();
}

TSharedPtr<SWidget> FHoverDecorator::CreateDecoratorWidget(const FTextRunInfo& RunInfo, const FTextBlockStyle& DefaultTextStyle) const
{
	TSharedPtr<SInteractableText> InteractableText = SNew(SInteractableText)
		.InText(RunInfo.Content)
		.InTextStyle(DefaultTextStyle)
		.InRichTextStyleSet(Owner->GetTextStyleSet())
		.InOwner(Owner);

	return InteractableText;
}

void FHoverDecorator::CreateDecoratorText(const FTextRunInfo& RunInfo, FTextBlockStyle& InOutTextStyle, FString& InOutString) const
{
}

TSharedPtr<ITextDecorator> UMemoryRichTextDecorator::CreateDecorator(URichTextBlock* InOwner)
{
	return MakeShareable(new FHoverDecorator(InOwner));
}