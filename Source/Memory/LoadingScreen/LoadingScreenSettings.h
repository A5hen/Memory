// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettingsBackedByCVars.h"
#include "LoadingScreenSettings.generated.h"

/**
 * 
 */
UCLASS(config = Game, defaultconfig, meta = (DisplayName = "Loading Screen"))
class MEMORY_API ULoadingScreenSettings : public UDeveloperSettingsBackedByCVars
{
	GENERATED_BODY()
	
public:

	ULoadingScreenSettings();

public:

	UPROPERTY(config, EditAnywhere, Category = "Display", meta = (MetaClass = "/Script/UMG.UserWidget"))
	FSoftClassPath LoadingScreenWidget;

	UPROPERTY(config, EditAnywhere, Category = "Display")
	int32 LoadingScreenZOrder = 10000;

	UPROPERTY(config, EditAnywhere, Category = "Configuration", meta = (ConsoleVariable = "LoadingScreen.HoldLoadingScreenAdditionalSecs"))
	float HoldLoadingScreenAdditionalSecs = 2.0f;

	UPROPERTY(config, EditAnywhere, Category = "Configuration")
	float LoadingScreenHeartbeatHangDuration = 0.0f;

	UPROPERTY(config, EditAnywhere, Category = "Configuration")
	float LogLoadingScreenHeartbeatInterval = 5.0f;

	UPROPERTY(config, EditAnywhere, Category = "Configuration")
	bool ForceTickLoadingScreenEvenInEditor = true;
	
	UPROPERTY(Transient, EditAnywhere, Category = "Debugging")
	bool HoldLoadingScreenAdditionalSecsEvenInEditor = false;

	UPROPERTY(Transient, EditAnywhere, Category = "Debugging", meta = (ConsoleVariable = "LoadingScreen.LogLoadingScreenReasonEveryFrame"))
	bool LogLoadingScreenReasonEveryFrame = false;

	UPROPERTY(Transient, EditAnywhere, Category = "Debugging", meta = (ConsoleVariable = "LoadingScreen.AlwaysShow"))
	bool ForceLoadingScreenVisible = false;
};