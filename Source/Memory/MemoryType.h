

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"//
#include "MemoryType.generated.h"//

struct FGeneratedBehavior;
struct FExperiencedEventInfomation;

typedef TMap<FGameplayTag, FGeneratedBehavior> TGeneratedCharacterBehaviors;
typedef TMap<FGameplayTag, FExperiencedEventInfomation> TExperiencedEventInfomation_AllStage;

USTRUCT()
struct FContentWidgetInfo
{
	GENERATED_BODY()

	FGameplayTag OwnerWidgetTag;
	FGameplayTag ContentTag;

	FGameplayTag EventStage;
	FGameplayTag EventTag;

	FGameplayTag CharacterTag;
	FName BehaviorDesc;
	int32 CognitionLevel;

	FGameplayTag SelfAwarenessTag;
};