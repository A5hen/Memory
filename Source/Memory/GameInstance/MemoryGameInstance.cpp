// Fill out your copyright notice in the Description page of Project Settings.


#include "MemoryGameInstance.h"

UMemoryEventSet* UMemoryGameInstance::GetMemoryEventSet()
{
    return MemoryEventSet;
}

UCharacterCognitionSet* UMemoryGameInstance::GetCharacterCognitionSet()
{
    return CharacterCognitionSet;
}

USelfAwarenessSet* UMemoryGameInstance::GetAwarenessSet()
{
    return SelfAwarenessSet;
}

 UExplanationSet* UMemoryGameInstance::GetExplanationSet()
{
    return ExplanationSet;
}