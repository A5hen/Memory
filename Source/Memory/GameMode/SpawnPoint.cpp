// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnPoint.h"
#include "Memory/GameMode/SpawnPointSubsystem.h"//

ASpawnPoint::ASpawnPoint()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ASpawnPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASpawnPoint::BeginPlay()
{
	Super::BeginPlay();
	
	if (USpawnPointSubsystem* SpawnPointSubsystem = UWorld::GetSubsystem<USpawnPointSubsystem>(GetWorld()))
	{
		SpawnPointSubsystem->RegisterSpawnPoint(this);
	}
}