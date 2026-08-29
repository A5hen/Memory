// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameplayTagContainer.h"//
#include "MemoryWidgetController.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;

class AMemoryPlayerController;
class AMemoryPlayerState;
class UMemoryAbilitySystemComponent;
class UMemoryAttributeSet;

struct FContentWidgetInfo;

USTRUCT(BlueprintType)
struct FWidgetControllerParams
{
	GENERATED_BODY()

	FWidgetControllerParams() {}
	FWidgetControllerParams(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
		: PlayerContrller(PC), PlayerState(PS), AbilitySystemComponent(ASC), AttributeSet(AS) {
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<APlayerController>PlayerContrller = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<APlayerState>PlayerState = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UAbilitySystemComponent>AbilitySystemComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UAttributeSet>AttributeSet = nullptr;
};

DECLARE_MULTICAST_DELEGATE_OneParam(FOnActivationStateChanged, bool);

DECLARE_MULTICAST_DELEGATE_OneParam(FOnContentSelected, const FContentWidgetInfo&);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnOtherContentSelected, const FContentWidgetInfo&);

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class MEMORY_API UMemoryWidgetController : public UObject
{
	GENERATED_BODY()
	
public:

	virtual void BroadcastInitialValues();

	void SetWidgetControllerParams(const FWidgetControllerParams& WCParams);

	virtual void BindCallBacksToDependencies();

	void SelectContent(const FContentWidgetInfo& ContentWidgetInfo);
	void DeselectPreviousContent(const FContentWidgetInfo& ContentWidgetInfo);

protected:

	AMemoryPlayerController* GetMemoryPC();
	AMemoryPlayerState* GetMemoryPS();
	UMemoryAbilitySystemComponent* GetMemoryASC();
	UMemoryAttributeSet* GetMemoryAS();

public:

	FOnContentSelected OnContentSelected;
	FOnOtherContentSelected OnOtherContentSelected;

	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<APlayerController>PlayerController;

	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<APlayerState>PlayerState;

	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<UAbilitySystemComponent>AbilitySystemComponent;

	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<UAttributeSet>AttributeSet;

protected:

	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<AMemoryPlayerController>MemoryPC;

	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<AMemoryPlayerState>MemoryPS;

	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<UMemoryAbilitySystemComponent>MemoryASC;

	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<UMemoryAttributeSet>MemoryAS;
};