// Fill out your copyright notice in the Description page of Project Settings.


#include "MemoryAbilitySystemLibrary.h"
#include "Kismet/GameplayStatics.h"//
#include "Memory/HUD/MemoryHUD.h"//
#include "Memory/UI/WidgetController/MemoryWidgetController.h"//

void UMemoryAbilitySystemLibrary::GetMemoryHUD(const UObject* WorldContextObject, AMemoryHUD*& OutHUD)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		OutHUD = Cast<AMemoryHUD>(PC->GetHUD());
	}
}

UMemoryWidgetController* UMemoryAbilitySystemLibrary::GetBaseWidgetController(const UObject* WorldContextObject)
{
	AMemoryHUD* MemoryHUD;
	GetMemoryHUD(WorldContextObject, MemoryHUD);
	if (MemoryHUD)
	{
		return MemoryHUD->GetBaseWidgetController();
	}

	return nullptr;
}

UMemoryWidgetController* UMemoryAbilitySystemLibrary::GetOverlayWidgetController(const UObject* WorldContextObject)
{
	AMemoryHUD* MemoryHUD;
	GetMemoryHUD(WorldContextObject, MemoryHUD);
	if (MemoryHUD)
	{
		return MemoryHUD->GetOverlayWidgetController();
	}

	return nullptr;
}

UMemoryWidgetController* UMemoryAbilitySystemLibrary::GetEventGraphWidgetController(const UObject* WorldContextObject)
{
	AMemoryHUD* MemoryHUD;
	GetMemoryHUD(WorldContextObject, MemoryHUD);
	if (MemoryHUD)
	{
		return MemoryHUD->GetEventGraphWidgetController();
	}

	return nullptr;
}

UMemoryWidgetController* UMemoryAbilitySystemLibrary::GetCognitionGraphWidgetController(const UObject* WorldContextObject)
{
	AMemoryHUD* MemoryHUD;
	GetMemoryHUD(WorldContextObject, MemoryHUD);
	if (MemoryHUD)
	{
		return MemoryHUD->GetCognitionGraphWidgetController();
	}

	return nullptr;
}