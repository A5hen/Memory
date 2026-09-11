// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameplayTagContainer.h"//
#include "Memory/Memory.h"//
#include "Memory/Interaction/InteractableTarget.h"//
#include "MemoryEventDefinition.generated.h"

class UEventAsyncAction;
class UListenDialogueSelectionResult;

class UMemoryGlobalAbilitySystem;
class USpawnPointSubsystem;

class UMemoryActivatableWidget;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEventSubstepStarted, int32, SubstepIndex);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnEventStepFinished, int32);

USTRUCT(BlueprintType)
struct FEventTriggerCondition
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FName, bool> BooleanConditions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FGameplayTag, int32> AttributeConditions;
};

USTRUCT(BlueprintType)
struct FEventCausedEffect
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FGameplayTagContainer GrantedAbilities;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TMap<FGameplayTag, int32> AttributeEffects;
};

USTRUCT()
struct FTypeToAsyncAction
{
	GENERATED_BODY()

	UPROPERTY()
	TMap<EActionType, TObjectPtr<UEventAsyncAction>> TypeToAsyncAction;
};

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class MEMORY_API UMemoryEventDefinition : public UObject
{
	GENERATED_BODY()

public:

	FOnEventStepFinished OnEventStepFinished;

	UPROPERTY(BlueprintAssignable, Category = "EventDefinition")
	FOnEventSubstepStarted OnEventSubstepStarted;

public:

	const FGameplayTag& GetEventTag() { return EventTag; }

	/*EventStep*/
	UFUNCTION(BlueprintImplementableEvent, Category = "EventDefinition")
	void StartEventStep(int32 StepIndex);

	UFUNCTION(BlueprintCallable, Category = "EventDefinition")
	void FinishEventStep(int32 StepIndex);

	int32 GetEventStepNum() const { return StepNum; }
	/*EventStep*/

	const TMap<FGameplayTag, TSubclassOf<AActor>>& GetSceneActorClass() const { return SceneActorClass; }

	void SetOutterWorldContext(UWorld* OutterWorldContext);
	void SetPlayerController(APlayerController* InPlayerController);

	/*AsyncAction*/
	void RegisterEventAsyncAction(UEventAsyncAction* ActionToActivate);
	void FinishEventAsyncAction(const FGameplayTag& ActorTag, EActionType ActionType);
	void PostFinishedActionsChange();
	bool CheckActionIsFinished(const FName& ActionName) const;

	void SendDialogueResult(const FGameplayTag& ActorTag, int32 SentenceIndex, FText Result);
	/*AsyncAction*/

	/*SceneActor*/
	void SceneSetup();

	void ClearSceneActor();

	AActor* GetSceneActorByActorTag(const FGameplayTag& ActorTag) const;
	/*SceneActor*/

protected:

	/*Effect*/
	UFUNCTION(BlueprintCallable, Category = "Action")
	void PushSelectionWidget(TSubclassOf<UMemoryActivatableWidget> SelectionWidgetClass, FGameplayTag ActorTag, const TArray<FText>& Content);

	UFUNCTION(BlueprintCallable, Category = "Action|Character")
	void SetDialogueContent(FGameplayTag ActorTag, const FDialogueContent& NewDialogueContent);

	UFUNCTION(BlueprintCallable, Category = "Action|Player")
	void GrantNewAbilities(FGameplayTagContainer AbilityTags);

	UFUNCTION(BlueprintCallable, Category = "Action|Player")
	void SwitchToInteractionCamera(FGameplayTag ActorTag);

	UFUNCTION(BlueprintCallable, Category = "Action|Player")
	void GenerateCharacterBehaviorCognition(const FGameplayTag& CharacterTag, const FName& BehaviorDesc);

	UFUNCTION(BlueprintCallable, Category = "Action|Player")
	void GenerateSelfAwareness(const FGameplayTag& AwarenessTag, bool bInGroup = false, int32 Index = -1);
	/*Effect*/

	UMemoryGlobalAbilitySystem* GetGlobalAbilitySystem();
	USpawnPointSubsystem* GetSpawnPointSubsystem();

protected:

	UPROPERTY()
	FGameplayTag EventTag;

	UPROPERTY(EditDefaultsOnly, Category = "TriggerCondition")
	FEventTriggerCondition TriggerCondition;

	UPROPERTY(EditDefaultsOnly, Category = "StepNum");
	int32 StepNum = 0;

	/*Subsystem*/
	UPROPERTY()
	TObjectPtr<UMemoryGlobalAbilitySystem> GlobalAbilitySystem;

	UPROPERTY()
	TObjectPtr<USpawnPointSubsystem> SpawnPointSubsystem;
	/*Subsystem*/

	/*SceneActor*/
	UPROPERTY(EditDefaultsOnly, Category = "SceneActor")
	TMap<FGameplayTag, TSubclassOf<AActor>> SceneActorClass;

	UPROPERTY()
	TMap<FGameplayTag, TObjectPtr<AActor>> SceneActors;

	UPROPERTY(EditDefaultsOnly, Category = "SceneActor|CharacterDialogueContent")
	TMap<FGameplayTag, FDialogueContent> CharacterDialogueContent;
	/*SceneActor*/

	/*AsyncAction*/
	UPROPERTY()
	TMap<FGameplayTag, FTypeToAsyncAction> ActiveEventAsyncActions;

	UPROPERTY()
	TMap<FName, TObjectPtr<UEventAsyncAction>> InactiveEventAsyncActions;

	UPROPERTY(EditDefaultsOnly, Category = "FinishedAction");
	TArray<FName> FinishedActions;
	/*AsyncAction*/

	/*Outter*/
	UPROPERTY()
	TObjectPtr<UWorld> WorldContext;

	UPROPERTY()
	TObjectPtr<APlayerController> PlayerController;
	/*Outter*/
};