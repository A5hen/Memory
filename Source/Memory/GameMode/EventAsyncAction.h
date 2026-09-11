// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "GameplayTagContainer.h"//
#include "Memory.h"//
#include "EventAsyncAction.generated.h"

class UMemoryEventDefinition;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOutputNode);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOutputNode_Dialogue, int32, SentenceIndex, FText, Result);

/**
 * 
 */
UCLASS(BlueprintType, meta = (ExposedAsyncProxy = "OutAsyncAction"))
class MEMORY_API UEventAsyncAction : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()
	
public:

	UPROPERTY(BlueprintAssignable)
	FOutputNode OnActionStarted;

	UPROPERTY(BlueprintAssignable)
	FOutputNode OnActionFinished;

	UPROPERTY(BlueprintAssignable)
	FOutputNode NextAsyncAction;

	UFUNCTION(BlueprintCallable, Category = "EventAsyncAction", 
		meta = (DefaultToSelf = "InEventDefinition", BlueprintInternalUseOnly = "true"))
	static UEventAsyncAction* EventAsyncAction(
		UMemoryEventDefinition* InEventDefinition,
		FName InActionName, EActionType InActionType, FGameplayTag InActorTag, const TArray<FName>& InStartCondition);

	virtual void Activate() override;

	void Destory();

	/*Output*/
	void Start();

	void Finish();

	void ActivateNextAsyncAction();
	/*Output*/

	void ListenDialogue(UListenDialogueResult* InListenDialogueResult);
	void SendDialogueResult(int32 SentenceIndex, FText Result);

	bool CheckStartCondition(const TArray<FName>& InFinishedActions) const;
	bool IsFinished() const { return bFinished; }

	const FName& GetActionName() const { return ActionName; }
	EActionType GetActionType() const { return ActionType; }
	const FGameplayTag& GetActorTag() const { return ActorTag; }

protected:

	UPROPERTY()
	TObjectPtr<UMemoryEventDefinition> OwnerEventDefinition;

	FName ActionName;

	EActionType ActionType;

	FGameplayTag ActorTag;

	TArray<FName> StartCondition;

	bool bFinished = false;

	UPROPERTY()
	TObjectPtr<UListenDialogueResult> ListenDialogueResult;
};

UCLASS(BlueprintType, meta = (ExposedAsyncProxy = "OutAsyncAction"))
class MEMORY_API UListenDialogueResult : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable)
	FOutputNode_Dialogue OnResultReceived;

	UFUNCTION(BlueprintCallable, Category = "EventAsyncAction",
		meta = (DefaultToSelf = "InEventDefinition", BlueprintInternalUseOnly = "true"))
	static UListenDialogueResult* ListenDialogueResult(UEventAsyncAction* InAsyncAction);

	virtual void Activate() override;

	void Destory();
};