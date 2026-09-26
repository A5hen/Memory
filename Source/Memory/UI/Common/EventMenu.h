// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MemoryActivatableWidget.h"
#include "Memory/MemoryType.h"//
#include "EventMenu.generated.h"

class UWidgetSwitcher;;
class UCommonButtonBase;

class UEventGraph;
class UEventDetail;

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

	virtual void OnContentSelected(const FContentWidgetInfo& ContentWidgetInfo) override;

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void ShowDetail();
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void HideDetail();

	void UpdateEventMenu(const TMap<EEventStage, FExperiencedEventInfomation>& ExperiencedEventInfomation_AllStage);
	void GenerateEventGraph(EEventStage EventStage, const FExperiencedEventInfomation& FExperiencedEventInfomation);
	void UpdateEventGraph(EEventStage EventStage, const FExperiencedEventInfomation& ExperiencedEventInfomation, bool bNewStage);

	void UpdateEventStageSwitcher(TArray<EEventStage> NewEventStages);
	void OnEventStageSelected(EEventStage TargetStage);

	void StartGraphScale();
	void EndGraphScale();

protected:

	/*EventGraph*/
	UPROPERTY(EditDefaultsOnly, Category = "EventGraph")
	TSubclassOf<UEventGraph> EventGraphClass;

	UPROPERTY(meta = (BindWidget))
	UWidgetSwitcher* GraphSwitcher;

	UPROPERTY()
	TMap<EEventStage, TObjectPtr<UEventGraph>> GeneratedEventGraphs;

	UPROPERTY(EditDefaultsOnly, Category = "EventGraph")
	EEventStage CurrentEventStage = EEventStage::None;

	UPROPERTY()
	TObjectPtr<UEventGraph> CurrentEventGraph;
	/*CharacterCognitionGraph*/

	UPROPERTY(meta = (BindWidget))
	UEventDetail* EventDetail;

	UPROPERTY(meta = (BindWidget))
	UCommonButtonBase* CoreWidgetJumpButton;

	UPROPERTY(EditDefaultsOnly, Category = "ScaleTag")
	FGameplayTag ScaleTag;

	bool bMouseDown = false;

	FVector2D MouseStartPosition;
	FVector2D MouseCurrentPosition;
	FWidgetTransform GraphStartTransform;

	bool bScalable = false;
};