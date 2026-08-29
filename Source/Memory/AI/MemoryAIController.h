// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MemoryAIController.generated.h"

class UBehaviorTreeComponent;

/**
 * 
 */
UCLASS()
class MEMORY_API AMemoryAIController : public AAIController
{
	GENERATED_BODY()

public:

	AMemoryAIController();

protected:

	UPROPERTY()
	TObjectPtr<UBehaviorTreeComponent>BehaviorTreeComponent;
};