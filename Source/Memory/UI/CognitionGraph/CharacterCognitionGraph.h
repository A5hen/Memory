// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Memory/UI/GraphWidget.h"
#include "GameplayTagContainer.h"//
#include "CharacterCognitionGraph.generated.h"

class UMemoryWidgetController;
class UCognitionGraphNode;

struct FBehaviorCognitionInfomation;

class UCharacterCognitionSet;

/**
 * 
 */
UCLASS()
class MEMORY_API UCharacterCognitionGraph : public UGraphWidget
{
	GENERATED_BODY()

public:

	virtual void SetWidgetController(UMemoryWidgetController* InWidgetController)override;
	virtual void ClearGraph()override;
	virtual void UnbindCallBacks() override;

protected:

	void UpdateCognitionGraph(const FBehaviorCognitionInfomation& BehaviorCognitionInfomation);

	UCharacterCognitionSet* GetCharacterCognitionSet();
	
protected:

	UPROPERTY()
	TMap<FName, TObjectPtr<UCognitionGraphNode>> GeneratedCognitionGraphNodes;

	UPROPERTY(EditDefaultsOnly, Category = "Node")
	TSubclassOf<UCognitionGraphNode> CognitionGraphNodeClass;

	FGameplayTag SelectedCharacter;

	UPROPERTY()
	TObjectPtr<UCharacterCognitionSet> CharacterCognitionSet;
};