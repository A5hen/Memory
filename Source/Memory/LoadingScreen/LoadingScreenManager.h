// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Tickable.h"//
#include "UObject/WeakInterfacePtr.h"//
#include "LoadingScreenManager.generated.h"

class ILoadingProcessInterface;

/**
 * 
 */
UCLASS()
class MEMORY_API ULoadingScreenManager : public UGameInstanceSubsystem, public FTickableGameObject
{
	GENERATED_BODY()

public:

	/*Subsystem Interface*/
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	/*End of Subsystem Interface*/

	/*TickableObjectBase Interface*/
	virtual void Tick(float DeltaTime) override;
	virtual ETickableTickType GetTickableTickType() const override;
	virtual bool IsTickable() const override;
	virtual TStatId GetStatId() const override;
	virtual UWorld* GetTickableGameObjectWorld() const override;
	/*End of TickableObjectBase Interface*/

	void RegisterLoadingProcessor(TScriptInterface<ILoadingProcessInterface> Interface);
	void UnregisterLoadingProcessor(TScriptInterface<ILoadingProcessInterface> Interface);

	DECLARE_MULTICAST_DELEGATE_OneParam(FOnLoadingScreenVisibilityChangedDelegate, bool);

private:

	void HandlePreLoadMap(const FWorldContext& WorldContext, const FString& MapName);
	void HandlePostLoadMap(UWorld* World);

	void UpdateLoadingScreen();

	bool CheckForAnyNeedToShowLoadingScreen();

	bool ShouldShowLoadingScreen();

	bool IsShowingInitialLoadingScreen() const;

	void ShowLoadingScreen();

	void HideLoadingScreen();

	void RemoveWidgetFromViewport();

	void StartBlockingInput();

	void StopBlockingInput();

	void ChangePerformanceSettings(bool bEnabingLoadingScreen);

private:

	FOnLoadingScreenVisibilityChangedDelegate LoadingScreenVisibilityChanged;

	TSharedPtr<SWidget> LoadingScreenWidget;

	TSharedPtr<IInputProcessor> InputPreProcessor;

	TArray<TWeakInterfacePtr<ILoadingProcessInterface>> ExternalLoadingProcessors;

	FString DebugReasonForShowingOrHidingLoadingScreen;

	float TimeLoadingScreenShown = 0.f;

	float TimeLoadingScreenLastDismissed = -1.f;

	float TimeUntilNextLogHeartbeatSeconds = 0.f;

	bool bCurrentlyInLoadMap = false;

	bool bCurrentlyShowingLoadingScreen = false;
};