// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayTagContainer.h"//
#include "SpawnPoint.generated.h"

UCLASS()
class MEMORY_API ASpawnPoint : public AActor
{
	GENERATED_BODY()
	
public:	

	ASpawnPoint();

	virtual void Tick(float DeltaTime) override;

	const FGameplayTag& GetPointTag() const { return PointTag; }

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Point Tag")
	FGameplayTag PointTag;

	virtual void BeginPlay() override;
};