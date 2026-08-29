// Fill out your copyright notice in the Description page of Project Settings.


#include "GraphContent_Explanation.h"
#include "Components/CanvasPanel.h"//
#include "Components/CanvasPanelSlot.h"//
#include "Blueprint/WidgetLayoutLibrary.h"//
#include "Components/SizeBox.h"//
#include "Memory/GameInstance/MemoryGameInstance.h"//
#include "Memory/UI/Explanation/ExplanationSet.h"//
#include "Memory/UI/GraphContentWidget.h"//
#include "Memory/Player/Cognition/CharacterCognitionSet.h"//

void UGraphContent_Explanation::ShowExplanation(bool bShow, FText InText)
{
	UExplanationSet* ExplanationSet = nullptr;
	if (UMemoryGameInstance* MemoryGI = GetGameInstance<UMemoryGameInstance>())
	{
		ExplanationSet = MemoryGI->GetExplanationSet();
	}
	if (!ExplanationSet)return;

	FName ExplanationID = FName(*InText.ToString());

	const FText* Explanation = ExplanationSet->GetExplanation(ExplanationID);

	ExplanationSizeBox->SetVisibility(bShow ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
}

FReply UGraphContent_Explanation::NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FVector2D Position = InGeometry.AbsoluteToLocal(InMouseEvent.GetScreenSpacePosition());

	ExplanationSizeBox->SetRenderTranslation(FVector2D(-100.f, Position.Y));

	return FReply::Handled();
}