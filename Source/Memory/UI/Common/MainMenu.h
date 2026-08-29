// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MemoryActivatableWidget.h"
#include "MainMenu.generated.h"

class UCommonButtonBase;

/**
 * 
 */
UCLASS()
class MEMORY_API UMainMenu : public UMemoryActivatableWidget
{
	GENERATED_BODY()
	
public:

	UMainMenu(const FObjectInitializer& ObjectInitializer);

protected:

	virtual void NativeOnInitialized() override;

	void HandleTabAction();

	void EventMenuButtonClicked();
	void CharacterCognitionMenuButtonClicked();

protected:

	UPROPERTY(EditDefaultsOnly, Category = "TriggerTag")
	FGameplayTag TriggerTag;

	UPROPERTY(meta = (BindWidget))
	UCommonButtonBase* EventMenuButton;

	UPROPERTY(meta = (BindWidget))
	UCommonButtonBase* CharacterCognitionMenuButton;
};