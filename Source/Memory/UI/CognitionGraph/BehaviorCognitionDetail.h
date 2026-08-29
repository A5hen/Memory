// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BehaviorCognitionDetail.generated.h"

class UTextBlock;
class UScrollBox;

class UGraphContentWidget;
struct FContentWidgetInfo;

class UCharacterCognitionSet;

/**
 * 
 */
UCLASS()
class MEMORY_API UBehaviorCognitionDetail : public UUserWidget
{
	GENERATED_BODY()

public:

	void UpdateContent(const FContentWidgetInfo& ContentWidgetInfo);
	
protected:

	UPROPERTY(meta = (BindWidget))
	UTextBlock* BehaviorDesc;

	UPROPERTY(meta = (BindWidget))
	UGraphContentWidget* Overview_Event;

	UPROPERTY(meta = (BindWidget))
	UScrollBox* ScrollBox_BehaviorCognition;

	UPROPERTY(EditDefaultsOnly, Category = "Content")
	TSubclassOf<UGraphContentWidget> Content_BehaviorCognitionClass;

	int32 CurrentCognitionLevel = -1;
};