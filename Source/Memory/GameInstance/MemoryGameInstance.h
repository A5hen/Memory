// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MemoryGameInstance.generated.h"

class UMemoryEventSet;

class UCharacterCognitionSet;
class USelfAwarenessSet;

class UExplanationSet;


/**
 * 
 */
UCLASS(BlueprintType)
class MEMORY_API UMemoryGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	UMemoryEventSet* GetMemoryEventSet();
	UCharacterCognitionSet* GetCharacterCognitionSet();
	USelfAwarenessSet* GetAwarenessSet();
	UExplanationSet* GetExplanationSet();

protected:

	UPROPERTY(EditDefaultsOnly, Category = "GameCore")
	TObjectPtr<UMemoryEventSet> MemoryEventSet;

	UPROPERTY(EditDefaultsOnly, Category = "GameCore")
	TObjectPtr<UCharacterCognitionSet> CharacterCognitionSet;
	
	UPROPERTY(EditDefaultsOnly, Category = "GameCore")
	TObjectPtr<USelfAwarenessSet> SelfAwarenessSet;

	UPROPERTY(EditDefaultsOnly, Category = "Explanation")
	TObjectPtr<UExplanationSet> ExplanationSet;
};