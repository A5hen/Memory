

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"//
#include "MemoryType.generated.h"//

struct FGeneratedBehavior;
struct FExperiencedEventInfomation;

typedef TMap<FGameplayTag, FGeneratedBehavior> TGeneratedCharacterBehaviorsType;
typedef TMap<FGameplayTag, FExperiencedEventInfomation> TExperiencedEventInfomationType_AllStage;

USTRUCT(BlueprintType)
struct FContentWidgetInfo
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	FGameplayTag OwnerWidgetTag;

	UPROPERTY(BlueprintReadWrite)
	FGameplayTag ContentTag;

	UPROPERTY(BlueprintReadWrite)
	FGameplayTag EventStage;

	UPROPERTY(BlueprintReadWrite)
	FGameplayTag EventTag;

	UPROPERTY(BlueprintReadWrite)
	FGameplayTag CharacterTag;

	UPROPERTY(BlueprintReadWrite)
	FName BehaviorDesc;

	UPROPERTY(BlueprintReadWrite)
	int32 CognitionLevel;

	UPROPERTY(BlueprintReadWrite)
	FGameplayTag SelfAwarenessTag;
};