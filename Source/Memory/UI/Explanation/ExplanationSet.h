// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ExplanationSet.generated.h"

/**
 * 
 */
UCLASS()
class MEMORY_API UExplanationSet : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:

	const FText* GetExplanation(const FName& ExplanationID) const;

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Explanations")
	TMap<FName, FText> Explanations;
};