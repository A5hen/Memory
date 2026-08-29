// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GameplayTagContainer.h"//
#include "CommonUIInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCommonUIInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MEMORY_API ICommonUIInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual void SetOwnerActorTag(const FGameplayTag& ActorTag) {}
};