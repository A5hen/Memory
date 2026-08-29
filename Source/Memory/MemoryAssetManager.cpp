// Fill out your copyright notice in the Description page of Project Settings.


#include "MemoryAssetManager.h"
#include "Memory/MemoryGameplayTag.h"//

UMemoryAssetManager& UMemoryAssetManager::Get()
{
	check(GEngine);
	UMemoryAssetManager* MemoryAssetManager = Cast<UMemoryAssetManager>(GEngine->AssetManager);
	return *MemoryAssetManager;
}

void UMemoryAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	FMemoryGameplayTags::InitializeNativeGameplayTags();
}