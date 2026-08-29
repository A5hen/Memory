// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MemoryGameModeBase.generated.h"

class UMemoryAbilitySet;

/**
 * 
 */
UCLASS()
class MEMORY_API AMemoryGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:

	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

protected:

	void WaitSpawnPointsRegistration();

	void OnSpawnPointsRegistered();
};