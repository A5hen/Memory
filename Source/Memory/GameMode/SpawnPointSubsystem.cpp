// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnPointSubsystem.h"
#include "Memory/GameMode/SpawnPoint.h"//

void USpawnPointSubsystem::RegisterSpawnPoint(ASpawnPoint* SpawnPoint)
{
	if(SpawnPoint)
	{
		const FGameplayTag& PointTag = SpawnPoint->GetPointTag();

		SpawnPoints.Add(PointTag, SpawnPoint);

		if (SpawnPoints.Num() >= MaxNum)
		{
			bAllRegistered = true;

			OnSpawnPointsRegistered.Broadcast();
		}
	}
}

AActor* USpawnPointSubsystem::GetSpawnPointByTag(const FGameplayTag& SpawnPointTag) const
{
	if (SpawnPoints.Find(SpawnPointTag))
	{
		return SpawnPoints[SpawnPointTag];
	}

	return nullptr;
}