// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "LoadingProcessInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class ULoadingProcessInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MEMORY_API ILoadingProcessInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	static bool ShouldShowLoadingScreen(UObject* TestObject, FString& OutReason);

	virtual bool ShouldShowLoadingScreen(FString& OutReason) const { return false; }
};