// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MemoryActivatableWidget.h"
#include "Memory/MemoryType.h"//
#include "EventMenu.generated.h"

class UScrollBox;
class UWidgetSwitcher;;
class UCommonButtonBase;

class UEventGraph;
class UEventDetail;

struct FExperiencedEventInfomation;

class UGraphContentWidget;
struct FContentWidgetInfo;

/**
 * 
 */
UCLASS()
class MEMORY_API UEventMenu : public UMemoryActivatableWidget
{
	GENERATED_BODY()
	
public:

	virtual void SetWidgetController(UMemoryWidgetController* InWidgetController) override;

protected:

	virtual void NativeOnInitialized() override;

	virtual void NativeOnActivated() override;
	virtual void NativeOnDeactivated() override;

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual FReply NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual FReply NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual FReply NativeOnMouseWheel(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	virtual void HandleCoreWidgetJump(const FContentWidgetInfo& ContentWidgetInfo) override;

	virtual void OnContentSelected(const FContentWidgetInfo& ContentWidgetInfo) override;

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void ShowDetail();
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void HideDetail();

	void UpdateEventMenu(const TMap<FGameplayTag, FExperiencedEventInfomation>& ExperiencedEventInfomation_AllStage);
	void GenerateEventGraph(const FGameplayTag& EventStage, const FExperiencedEventInfomation& ExperiencedEventInfomation);

	void UpdateEventStageSwitcher(const FGameplayTagContainer& NewEventStages);
	void OnEventStageSelected(const FContentWidgetInfo& ContentWidgetInfo);

	void StartGraphScale();
	void EndGraphScale();

protected:

	UPROPERTY(meta = (BindWidget))
	UScrollBox* ScrollBox_EventStage;

	FGameplayTagContainer SelectableEventStages;

	/*EventGraph*/
	UPROPERTY(EditDefaultsOnly, Category = "EventMenu")
	TSubclassOf<UEventGraph> EventGraphClass;

	UPROPERTY(meta = (BindWidget))
	UWidgetSwitcher* GraphSwitcher;

	UPROPERTY()
	TMap<FGameplayTag, TObjectPtr<UEventGraph>> GeneratedEventGraphs;

	UPROPERTY(EditDefaultsOnly, Category = "EventMenu")
	FGameplayTag CurrentEventStage;

	UPROPERTY()
	TObjectPtr<UEventGraph> CurrentEventGraph;
	/*CharacterCognitionGraph*/

	UPROPERTY(meta = (BindWidget))
	UEventDetail* EventDetail;

	UPROPERTY(EditDefaultsOnly, Category = "Overview_Event")
	TSubclassOf<UGraphContentWidget> OverviewClass_Event;

	UPROPERTY(meta = (BindWidget))
	UCommonButtonBase* CoreWidgetJumpButton;

	UPROPERTY(EditDefaultsOnly, Category = "ScaleTag")
	FGameplayTag ScaleTag;

	bool bMouseDown = false;

	FVector2D MouseStartPosition;
	FVector2D MouseCurrentPosition;
	FWidgetTransform GraphStartTransform;

	bool bScalable = false;

	bool bFirstUpdate = true;
};