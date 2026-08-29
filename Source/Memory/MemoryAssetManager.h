// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "MemoryAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class MEMORY_API UMemoryAssetManager : public UAssetManager
{
	GENERATED_BODY()

public:

	static UMemoryAssetManager& Get();

protected:

	virtual void StartInitialLoading() override;
};