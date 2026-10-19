// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"//
#include "GameplayTagContainer.h"//
#include "Memory/Memory.h"//
#include "Memory/MemoryType.h"//
#include "MemoryPlayerState.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;

class USelfAwarenessSet;
struct FAwarenessInfo;

USTRUCT(BlueprintType)
struct FNameArray
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FName> Names;
};

USTRUCT(BlueprintType)
struct FExperiencedEventInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TMap<FGameplayTag, FNameArray> GeneratedCharacterBehavior;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FGameplayTagContainer GeneratedSelfAwareness;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FGameplayTagContainer GrantedAbilities;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TMap<FGameplayTag, int32> CausedAttributeEffects;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TMap<FGameplayTag, FVector2D> RelativePositions;
};

USTRUCT(BlueprintType)
struct FExperiencedEventInfomation
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TMap<FGameplayTag, FExperiencedEventInfo> TagToInfo;
}; 

USTRUCT(BlueprintType)
struct FGeneratedBehaviorCognition
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CurrentCognitionLevel = -1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<int32, FGameplayTagContainer> CognitionLevelToAwareness;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTagContainer Source;
};

USTRUCT(BlueprintType)
struct FGeneratedBehavior
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FName, FGeneratedBehaviorCognition> DescToCognition;
};

DECLARE_MULTICAST_DELEGATE_OneParam(FOnSelfAwarenessChanged, const FGameplayTag&);

DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnCharacterBehaviorUpdated, const FGameplayTag&, const FGeneratedBehavior&, bool);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnCharacterBehaviorsUpdated, const TGeneratedCharacterBehaviors&);

USTRUCT(BlueprintType)
struct FSelfAwarenessInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTagContainer Source;
};

/**
 * 
 */
UCLASS()
class MEMORY_API AMemoryPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:

	AMemoryPlayerState();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const { return AttributeSet; };

	/**/
	void SetPawnData();
	/**/

	void UpdateCharacterBehaviorCognition(const FGameplayTag& CharacterTag, const FName& BehaviorDesc, const FGameplayTag& EventTag);

	void GenerateSelfAwareness(const FGameplayTag& AwarenessTag, const FGameplayTag& EventTag, bool bInGroup = false, int32 Index = -1);
	void HandleSelfAwarenessGeneration(
		const FGameplayTagContainer& AwarenessTags, const FAwarenessInfo* InAwarenessInfo,
		TMap<FGameplayTag, FGeneratedBehavior>& ChangedCharacterBehaviors);

	const FExperiencedEventInfomation* GetExperiencedEventInfomation(FGameplayTag EventStageTag) const;

	const FGeneratedBehavior* GetGeneratedBehavior(const FGameplayTag& CharacterTag) const;
	const TGeneratedCharacterBehaviors& GetGeneratedCharacterBehaviors() const;

	const TExperiencedEventInfomation_AllStage& GetExperiencedEventInfomation_AllStage() const;

public:

	FOnSelfAwarenessChanged OnSelfAwarenessChanged;

	FOnCharacterBehaviorUpdated OnCharacterBehaviorUpdated;
	FOnCharacterBehaviorsUpdated OnCharacterBehaviorsUpdated;

protected:

	USelfAwarenessSet* GetSelfAwarenessSet();

protected:

	UPROPERTY(EditDefaultsOnly, Category = "GrantedAbility")
	FGameplayTagContainer GrantedAbilityTags;

	/*Event*/
	UPROPERTY(EditDefaultsOnly, Category = "ExperiencedEvent")
	TMap<FGameplayTag, FExperiencedEventInfomation> ExperiencedEventInfomation_AllStage;
	/*Event*/

	/*CharacterBehavior*/
	UPROPERTY(EditDefaultsOnly, Category = "CharacterBehavior")
	TMap<FGameplayTag, FGeneratedBehavior> GeneratedCharacterBehaviors;

	UPROPERTY(EditDefaultsOnly, Category = "CharacterBehavior")
	TMap<FGameplayTag, FGeneratedBehavior> UngenerateCharacterBehaviors;
	/*CharacterBehavior*/

	/*SelfAwareness*/
	UPROPERTY(EditDefaultsOnly, Category = "SelfAwareness_Single")
	TMap<FGameplayTag, FSelfAwarenessInfo> SelfAwarenessInfomation_Single;

	UPROPERTY(EditDefaultsOnly, Category = "SelfAwareness_Group")
	TMap<int32, FGameplayTagContainer>SelfAwarenessInfomation_Group;

	UPROPERTY()
	TObjectPtr<USelfAwarenessSet> SelfAwarenessSet;
	/*SelfAwareness*/

private:

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;
};