// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#define ECC_Interaction ECC_GameTraceChannel1

UENUM(BlueprintType)
enum class EActionType : uint8
{
	Dialogue,
	Selection,
	Move,
	None,
};

UENUM(BlueprintType)
enum class EEventStage : uint8
{
	Childhood,
	None,
};