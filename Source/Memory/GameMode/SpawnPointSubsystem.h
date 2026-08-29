// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "GameplaytagContainer.h"//
#include "SpawnPointSubsystem.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnSpawnPointsRegistered);

class ASpawnPoint;

/**
 * 
 */
UCLASS()
class MEMORY_API USpawnPointSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:

	FOnSpawnPointsRegistered OnSpawnPointsRegistered;

	void RegisterSpawnPoint(ASpawnPoint* SpawnPoint);

	bool IsAllRegistered() const { return bAllRegistered; }

	AActor* GetSpawnPointByTag(const FGameplayTag& SpawnPointTag) const;

protected:

	//TO DO: Map->Num
	int32 MaxNum = 1;

	bool bAllRegistered = false;

	UPROPERTY()
	TMap<FGameplayTag, ASpawnPoint*> SpawnPoints;
};