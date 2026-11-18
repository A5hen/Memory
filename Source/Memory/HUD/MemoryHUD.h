// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MemoryHUD.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;

class UPrimaryGameLayout;

class UMemoryActivatableWidget;

struct FWidgetControllerParams;
class UMemoryWidgetController;
class UOverlayWidgetController;
class UEventGraphWidgetController;
class UCognitionGraphWidgetController;

/**
 * 
 */
UCLASS()
class MEMORY_API AMemoryHUD : public AHUD
{
	GENERATED_BODY()

public:

	void InitRootLayout();

	void InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);

	UPrimaryGameLayout* GetRootLayout() const;

	bool MakeWidgetControllerParams(FWidgetControllerParams& OutParams);
	UMemoryWidgetController* GetOverlayWidgetController();
	UMemoryWidgetController* GetEventGraphWidgetController();
	UMemoryWidgetController* GetCognitionGraphWidgetController();
	
protected:

	/*RootLayout*/
	UPROPERTY(EditDefaultsOnly, Category = "RootLayout")
	TSubclassOf<UPrimaryGameLayout> RootLayoutClass;

	UPROPERTY()
	TObjectPtr<UPrimaryGameLayout> RootLayout;
	/*RootLayout*/

	/*Overlay*/
	UPROPERTY(EditDefaultsOnly, Category = "Overlay")
	TSubclassOf<UMemoryActivatableWidget> OverlayWidgetClass;

	UPROPERTY()
	TObjectPtr<UMemoryActivatableWidget> Overlay;

	UPROPERTY(EditDefaultsOnly, Category = "Overlay")
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;

	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;
	/*Overlay*/

	/*EventGraph*/
	UPROPERTY(EditDefaultsOnly, Category = "EventGraph")
	TSubclassOf<UEventGraphWidgetController> EventGraphWidgetControllerClass;

	UPROPERTY()
	TObjectPtr<UEventGraphWidgetController> EventGraphWidgetController;
	/*EventGraph*/

	/*CognitionGraph*/
	UPROPERTY(EditDefaultsOnly, Category = "CognitionGraph")
	TSubclassOf<UCognitionGraphWidgetController> CognitionGraphWidgetControllerClass;

	UPROPERTY()
	TObjectPtr<UCognitionGraphWidgetController> CognitionGraphWidgetController;
	/*CognitionGraph*/
};