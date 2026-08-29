// Fill out your copyright notice in the Description page of Project Settings.


#include "MemoryGameModeBase.h"
#include "Memory/GameMode/MemoryGameStateBase.h"//
#include "Memory/GameMode/SpawnPointSubsystem.h"//
#include "Memory/GameMode/MemoryEventManager.h"//

void AMemoryGameModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
    Super::InitGame(MapName, Options, ErrorMessage);

    GetWorld()->GetTimerManager().SetTimerForNextTick(this, &AMemoryGameModeBase::WaitSpawnPointsRegistration);
}

void AMemoryGameModeBase::WaitSpawnPointsRegistration()
{
    if(USpawnPointSubsystem* SpawnPointSubsystem = GetWorld()->GetSubsystem<USpawnPointSubsystem>())
    {
        if(SpawnPointSubsystem->IsAllRegistered())
        {
            OnSpawnPointsRegistered();
        }
        else
        {
            SpawnPointSubsystem->OnSpawnPointsRegistered.AddUObject(this, &AMemoryGameModeBase::OnSpawnPointsRegistered);
        }
    }
}

void AMemoryGameModeBase::OnSpawnPointsRegistered()
{
    if (UMemoryEventManager* EventManager = GetWorld()->GetSubsystem<UMemoryEventManager>())
    {
        EventManager->SetOutterWorldContext(GetWorld());
        EventManager->ConfirmStartEventCondition("SpawnPoint");
    }
}