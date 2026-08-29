// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/RichTextBlock.h"
#include "MemoryRichText.generated.h"

/**
 * 
 */
UCLASS()
class MEMORY_API UMemoryRichText : public URichTextBlock
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "MemoryRichText")
	void SetOwner(UObject* InOwner) { Owner = InOwner; }

	UFUNCTION(BlueprintCallable, Category = "MemoryRichText")
	UObject* GetOwner() const { return Owner; }

protected:

	UPROPERTY()
	TObjectPtr<UObject> Owner;
};