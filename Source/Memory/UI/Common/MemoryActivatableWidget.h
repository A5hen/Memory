// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "GameplayTagContainer.h"//
#include "Memory/UI/Common/CommonUIInterface.h"//
#include "Memory/UI/GraphContentWidget.h"//
#include "MemoryActivatableWidget.generated.h"

struct FUIInputConfig;

class UMemoryWidgetController;

UENUM(BlueprintType)
enum class EMemoryWidgetInputMode : uint8
{
	Default,
	GameAndMenu,
	Game,
	Menu
};

/**
 * 
 */
UCLASS()
class MEMORY_API UMemoryActivatableWidget : public UCommonActivatableWidget, public ICommonUIInterface
{
	GENERATED_BODY()

public:

	/*CommonActivatableWidget Interface*/
	virtual TOptional<FUIInputConfig> GetDesiredInputConfig() const override;
	/*End of CommonActivatableWidget Interface*/

	/*CommonUIInterface Interface*/
	virtual void SetOwnerActorTag(const FGameplayTag& ActorTag) override;
	/*End of CommonUIInterface Interface*/

	virtual void SetWidgetController(UMemoryWidgetController* InWidgetController);

	const FGameplayTag& GetWidgetTag() const;

protected:

	virtual void NativeOnActivated() override;
	virtual void NativeOnDeactivated() override;

	UMemoryActivatableWidget* PushCoreWidget(const FGameplayTag& InWidgetTag, const FGameplayTag& LayerTag);

	void JumpToCoreWidget();

	virtual void OnContentSelected(const FContentWidgetInfo& ContentWidgetInfo);
	void ReactContentSelection();

protected:

	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<UMemoryWidgetController>WidgetController;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	EMemoryWidgetInputMode InputConfig = EMemoryWidgetInputMode::Default;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	EMouseCaptureMode MouseCaptureMode = EMouseCaptureMode::CapturePermanently;

	UPROPERTY(EditDefaultsOnly, Category = "WidgetTag")
	FGameplayTag WidgetTag;

	UPROPERTY(BlueprintReadOnly, Category = "OwnerActorTag")
	FGameplayTag OwnerActorTag;

	/*ReactContentSelection*/
	bool bReactContentSelection = false;

	FGameplayTag TargetCoreWidget;
	/*ReactContentSelection*/
};