// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MemoryAbilitySystemLibrary.generated.h"

struct FWidgetControllerParams;
class AMemoryHUD;
class UMemoryWidgetController;
class UOverlayWidgetController;
class UEventGraphWidgetController;
class UCognitionGraphWidgetController;

/**
 * 
 */
UCLASS()
class MEMORY_API UMemoryAbilitySystemLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:

	static void GetMemoryHUD(const UObject* WorldContextObject, AMemoryHUD*& OutHUD);

	UFUNCTION(BlueprintPure, Category = "MemoryAbilitySystemLibrary", meta = (DefaultToSelf = "WorldContextObject"))
	static UMemoryWidgetController* GetBaseWidgetController(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category = "MemoryAbilitySystemLibrary", meta = (DefaultToSelf = "WorldContextObject"))
	static UMemoryWidgetController* GetOverlayWidgetController(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category = "MemoryAbilitySystemLibrary", meta = (DefaultToSelf = "WorldContextObject"))
	static UMemoryWidgetController* GetEventGraphWidgetController(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category = "MemoryAbilitySystemLibrary", meta = (DefaultToSelf = "WorldContextObject"))
	static UMemoryWidgetController* GetCognitionGraphWidgetController(const UObject* WorldContextObject);
};