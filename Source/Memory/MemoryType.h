

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"//

struct FGeneratedBehavior;
struct FExperiencedEventInfomation;

UENUM(BlueprintType)
enum class EEventStage : uint8
{
	Childhood,
	None,
};

typedef TMap<FGameplayTag, FGeneratedBehavior> TGeneratedCharacterBehaviors;
typedef TMap<EEventStage, FExperiencedEventInfomation> TExperiencedEventInfomation_AllStage;