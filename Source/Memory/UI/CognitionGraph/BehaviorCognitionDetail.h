// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameplayTagContainer.h"//
#include "BehaviorCognitionDetail.generated.h"

class UTextBlock;
class UScrollBox;

class UGraphContentWidget;
struct FGeneratedBehaviorCognition;

/**
 * 
 */
UCLASS()
class MEMORY_API UBehaviorCognitionDetail : public UUserWidget
{
	GENERATED_BODY()

public:

	void UpdateDetail(const FGameplayTag& InCharacterTag, FName InBehaviorDesc, const FGeneratedBehaviorCognition& GeneratedBehaviorCognition);
	
protected:

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text_BehaviorDesc;

	UPROPERTY(meta = (BindWidget))
	UScrollBox* ScrollBox_BehaviorCognition;

	UPROPERTY(EditDefaultsOnly, Category = "Content")
	TSubclassOf<UGraphContentWidget> Content_BehaviorCognitionClass;

	int32 CurrentCognitionLevel = -1;

	FGameplayTag CharacterTag;
	FName BehaviorDesc;
};