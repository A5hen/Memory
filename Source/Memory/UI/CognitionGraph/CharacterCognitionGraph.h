// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Memory/UI/GraphWidget.h"
#include "GameplayTagContainer.h"//
#include "CharacterCognitionGraph.generated.h"

class UCognitionGraphNode;

struct FGeneratedBehavior;

class UCharacterCognitionSet;

/**
 * 
 */
UCLASS()
class MEMORY_API UCharacterCognitionGraph : public UGraphWidget
{
	GENERATED_BODY()

public:

	virtual void ClearGraph()override;

	void UpdateCognitionGraph(const FGeneratedBehavior& GeneratedBehavior);

	const FGameplayTag& GetCharacterTag() const { return CharacterTag; }
	void SetCharacterTag(const FGameplayTag& InCharacterTag) { CharacterTag = InCharacterTag; }

protected:

	UCharacterCognitionSet* GetCharacterCognitionSet();
	
protected:

	FGameplayTag CharacterTag;

	UPROPERTY(EditDefaultsOnly, Category = "Node")
	TSubclassOf<UCognitionGraphNode> CognitionGraphNodeClass;

	UPROPERTY()
	TMap<FName, TObjectPtr<UCognitionGraphNode>> GeneratedCognitionGraphNodes;

	UPROPERTY()
	TObjectPtr<UCharacterCognitionSet> CharacterCognitionSet;
};