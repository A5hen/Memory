// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MemoryWidgetController.h"
#include "Memory/Memory.h"//
#include "GameplayTagContainer.h"//
#include "EventGraphWidgetController.generated.h"

struct FExperiencedEventInfomation;

DECLARE_MULTICAST_DELEGATE_OneParam(FUpdateEventGraph , const FExperiencedEventInfomation&);

struct FGraphTransform
{
	FVector2D GraphOffset;

	float GraphScale;
};

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class MEMORY_API UEventGraphWidgetController : public UMemoryWidgetController
{
	GENERATED_BODY()
	
public:

	FUpdateEventGraph UpdateEventGraph;

	virtual void BroadcastInitialValues() override;

	virtual void BindCallBacksToDependencies() override;

	void RecordGraphTransform_Stage(const FVector2D& Offset, float Scale);
	const FGraphTransform* GetGraphTransform_Stage(EEventStage InEventStage);

	void SwitchEventStage(EEventStage TargetEventStage);

protected:

	UPROPERTY(EditDefaultsOnly, Category = "EventStage")
	EEventStage CurrentEventStage;

	UPROPERTY(EditDefaultsOnly, Category = "EventStage")
	EEventStage EventStage_Graph;

	TMap<EEventStage, FGraphTransform> GraphTransform_Stage;
};