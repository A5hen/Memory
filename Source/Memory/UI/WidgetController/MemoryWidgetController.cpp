// Fill out your copyright notice in the Description page of Project Settings.


#include "MemoryWidgetController.h"
#include "Memory/Player/MemoryPlayerController.h"//
#include "Memory/Player/MemoryPlayerState.h"//
#include "Memory/AbilitySystem/MemoryAbilitySystemComponent.h"//
#include "Memory/AbilitySystem/MemoryAttributeSet.h"//

void UMemoryWidgetController::BroadcastInitialValues()
{
}

void UMemoryWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& WCParams)
{
	PlayerController = WCParams.PlayerContrller;
	PlayerState = WCParams.PlayerState;
	AttributeSet = WCParams.AttributeSet;
	AbilitySystemComponent = WCParams.AbilitySystemComponent;
}

void UMemoryWidgetController::BindCallBacksToDependencies()
{
}

void UMemoryWidgetController::SelectContent(const FContentWidgetInfo& ContentWidgetInfo)
{
	OnContentSelected.Broadcast(ContentWidgetInfo);
}

AMemoryPlayerController* UMemoryWidgetController::GetMemoryPC()
{
	if (MemoryPC == nullptr)
	{
		MemoryPC = Cast<AMemoryPlayerController>(PlayerController);
	}

	return MemoryPC;
}

AMemoryPlayerState* UMemoryWidgetController::GetMemoryPS()
{
	if(MemoryPS == nullptr)
	{
		MemoryPS = Cast<AMemoryPlayerState>(PlayerState);
	}

	return MemoryPS;
}

UMemoryAbilitySystemComponent* UMemoryWidgetController::GetMemoryASC()
{
	if (MemoryASC == nullptr)
	{
		MemoryASC = Cast<UMemoryAbilitySystemComponent>(AbilitySystemComponent);
	}

	return MemoryASC;
}

UMemoryAttributeSet* UMemoryWidgetController::GetMemoryAS()
{
	if(MemoryAS == nullptr)
	{
		MemoryAS = Cast<UMemoryAttributeSet>(AttributeSet);
	}

	return nullptr;
}