// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameplayTagContainer.h"//
#include "GraphContentWidget.generated.h"

class UMemoryWidgetController;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBP_OnSelected);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBP_OnDeselected);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnSelected, const FContentWidgetInfo&);

USTRUCT()
struct FContentWidgetInfo
{
	GENERATED_BODY()

	FGameplayTag OwnerWidgetTag;
	FGameplayTag ContentTag;

	FGameplayTag EventTag;

	FGameplayTag CharacterTag;
	FName BehaviorDesc;
	int32 CognitionLevel;

	FGameplayTag SelfAwarenessTag;
};

USTRUCT(BlueprintType)
struct FContentDisplayInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Event;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Character;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText BehaviorDesc;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CognitionLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText BehaviorCognition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText SelfAwareness;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDisplayContentDelegate, const FContentDisplayInfo&, Info);

/**
 * 
 */
UCLASS()
class MEMORY_API UGraphContentWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	void HandleMouseButtonDown();

	void DisplayContent();

protected:

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	void HandleDeselection(const FContentWidgetInfo& InContentWidgetInfo);

public:

	FOnSelected OnSelected;

	FContentWidgetInfo ContentWidgetInfo;

	UPROPERTY(BlueprintAssignable, Category = "ContentDisplay")
	FDisplayContentDelegate DisplayContentDelegate;

	UPROPERTY(BlueprintReadOnly, Category = "ContentDisplay")
	FContentDisplayInfo ContentDisplayInfo;

protected:

	UPROPERTY(BlueprintAssignable, Category = "Selection")
	FBP_OnSelected BP_OnSelected;

	UPROPERTY(BlueprintAssignable, Category = "Selection")
	FBP_OnDeselected BP_OnDeselected;

	UPROPERTY()
	TObjectPtr<UMemoryWidgetController> WidgetController;

	bool bSelected = false;
};