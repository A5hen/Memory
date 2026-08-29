// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Memory/UI/GraphContentWidget.h"
#include "Memory/UI/Explanation/ExplanationInterface.h"//
#include "GraphContent_Explanation.generated.h"

class UCanvasPanel;
class USizeBox;

/**
 * 
 */
UCLASS()
class MEMORY_API UGraphContent_Explanation : public UGraphContentWidget, public IExplanationInterface
{
	GENERATED_BODY()

public:

	/*Explanation Interface*/
	virtual void ShowExplanation(bool bShow, FText InText) override;
	/*End of Explanation Interface*/

protected:

	virtual FReply NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	
protected:

	UPROPERTY(meta = (BindWidget))
	USizeBox* ExplanationSizeBox;
};
