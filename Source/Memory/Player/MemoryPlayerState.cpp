// Fill out your copyright notice in the Description page of Project Settings.


#include "MemoryPlayerState.h"
#include "Kismet/GameplayStatics.h"//
#include "Memory/AbilitySystem/MemoryAbilitySystemComponent.h"//
#include "Memory/AbilitySystem/MemoryAttributeSet.h"//
#include "Memory/AbilitySystem/MemoryGlobalAbilitySystem.h"//
#include "Memory/GameInstance/MemoryGameInstance.h"//
#include "Memory/Interaction/InteractableTarget.h"
#include "Memory/Player/Awareness/SelfAwarenessSet.h"//

AMemoryPlayerState::AMemoryPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UMemoryAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Full);

	AttributeSet = CreateDefaultSubobject<UMemoryAttributeSet>("AttributeSet");
}

UAbilitySystemComponent* AMemoryPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AMemoryPlayerState::SetPawnData()
{
	//Grant Abilities
	UMemoryGlobalAbilitySystem* GlobalAbilitySystem = GetWorld()->GetSubsystem<UMemoryGlobalAbilitySystem>();
	if (GlobalAbilitySystem)
	{
		GlobalAbilitySystem->GrantAbilitiesToAbilitySystem(GrantedAbilityTags);
	}
}

void AMemoryPlayerState::UpdateCharacterBehaviorCognition(const FGameplayTag& CharacterTag, const FName& BehaviorDesc, const FGameplayTag& EventTag)
{
	bool bNewCharacter = false;

	FGeneratedBehaviorCognition* ChangedBehaviorCognition = nullptr;

	FGeneratedBehavior* GeneratedBehavior = nullptr;
	if (!GeneratedCharacterBehaviors.Contains(CharacterTag))
	{
		bNewCharacter = true;

		GeneratedBehavior = &GeneratedCharacterBehaviors.Add(CharacterTag);
	}
	else
	{
		GeneratedBehavior = GeneratedCharacterBehaviors.Find(CharacterTag);
	}

	if (!bNewCharacter)
	{
		if (FGeneratedBehaviorCognition* GeneratedBehaviorCognition = GeneratedBehavior->DescToCognition.Find(BehaviorDesc))
		{
			GeneratedBehaviorCognition->Source.AddTag(EventTag);

			ChangedBehaviorCognition = GeneratedBehaviorCognition;
		}
	}

	FGeneratedBehavior* UngenerateBehavior = UngenerateCharacterBehaviors.Find(CharacterTag);
	if (!ChangedBehaviorCognition && UngenerateBehavior)
	{
		if (FGeneratedBehaviorCognition* UngenerateBehaviorCognition = UngenerateBehavior->DescToCognition.Find(BehaviorDesc))
		{
			UngenerateBehaviorCognition->Source.AddTag(EventTag);

			GeneratedBehavior->DescToCognition.Emplace(BehaviorDesc, *UngenerateBehaviorCognition);
			UngenerateBehavior->DescToCognition.Remove(BehaviorDesc);

			ChangedBehaviorCognition = UngenerateBehaviorCognition;
		}
	}

	if (!ChangedBehaviorCognition)
	{
		FGeneratedBehaviorCognition NewBehaviorCognition;
		NewBehaviorCognition.CurrentCognitionLevel = 0;
		NewBehaviorCognition.Source.AddTag(EventTag);

		GeneratedBehavior->DescToCognition.Emplace(BehaviorDesc, NewBehaviorCognition);

		ChangedBehaviorCognition = &NewBehaviorCognition;
	}

	OnCharacterBehaviorUpdated.Broadcast(CharacterTag, *GeneratedBehavior, bNewCharacter);
}

void AMemoryPlayerState::GenerateSelfAwareness(const FGameplayTag& AwarenessTag, const FGameplayTag& EventTag, bool bInGroup, int32 Index)
{
	if (GetSelfAwarenessSet())return;

	if (FSelfAwarenessInfo* Info = SelfAwarenessInfomation_Single.Find(AwarenessTag))
	{
		Info->Source.AddTag(EventTag);

		//TODO: Broadcast SelfAwareness Changed
		return;
	}

	TMap<FGameplayTag, FGeneratedBehavior> ChangedCharacterBehaviors;

	FSelfAwarenessInfo NewInfo;
	NewInfo.Source.AddTag(EventTag);

	SelfAwarenessInfomation_Single.Emplace(AwarenessTag, NewInfo);

	const FAwarenessInfo* AwarenessInfo_Single = SelfAwarenessSet->GetAwarenessInfo_Single(AwarenessTag);

	FGameplayTagContainer TagContainer_Single;
	TagContainer_Single.AddTag(AwarenessTag);

	HandleSelfAwarenessGeneration(TagContainer_Single, AwarenessInfo_Single, ChangedCharacterBehaviors);

	if (bInGroup)
	{
		const FGameplayTagContainer* TagContainerkey = SelfAwarenessSet->GetTagContainerKey(Index);
		if (TagContainerkey && !TagContainerkey->IsEmpty())
		{
			TArray<FGameplayTag> KeyArray;
			SelfAwarenessInfomation_Single.GenerateKeyArray(KeyArray);

			FGameplayTagContainer GeneratedAwareness;
			GeneratedAwareness.AppendTags(FGameplayTagContainer::CreateFromArray(KeyArray));
			
			if (GeneratedAwareness.HasAllExact(*TagContainerkey))
			{
				const FAwarenessInfo* Awareness_Group = SelfAwarenessSet->GetAwarenessInfo_Group(Index);

				SelfAwarenessInfomation_Group.Emplace(Index, *TagContainerkey);

				HandleSelfAwarenessGeneration(*TagContainerkey, Awareness_Group, ChangedCharacterBehaviors);
			}
		}
	}

	if (!ChangedCharacterBehaviors.IsEmpty())
	{
		OnCharacterBehaviorsUpdated.Broadcast(ChangedCharacterBehaviors);
	}
}

void AMemoryPlayerState::HandleSelfAwarenessGeneration(
	const FGameplayTagContainer& AwarenessTags, const FAwarenessInfo* InAwarenessInfo,
	TMap<FGameplayTag, FGeneratedBehavior>& ChangedCharacterBehaviors)
{
	if (!InAwarenessInfo)return;

	for (const auto& CharacterBehaviorCognitionEffect : InAwarenessInfo->CharacterBehaviorCognitionEffects)
	{
		FGeneratedBehavior* GeneratedBehavior = GeneratedCharacterBehaviors.Find(CharacterBehaviorCognitionEffect.Key);
		FGeneratedBehavior& ChangedBehavior = ChangedCharacterBehaviors.FindOrAdd(CharacterBehaviorCognitionEffect.Key);

		for (const auto& Pair : CharacterBehaviorCognitionEffect.Value.NewCognitionLevel)
		{
			bool bBehaviorGenerated = false;

			if (GeneratedBehavior)
			{
				if (FGeneratedBehaviorCognition* GeneratedBehaviorCognition = GeneratedBehavior->DescToCognition.Find(Pair.Key))
				{
					GeneratedBehaviorCognition->CognitionLevelToAwareness.Emplace(Pair.Value, AwarenessTags);

					ChangedBehavior.DescToCognition.Emplace(Pair.Key, *GeneratedBehaviorCognition);

					bBehaviorGenerated = true;
				}
			}

			if (!bBehaviorGenerated)
			{
				FGeneratedBehavior& UngenerateBehavior = UngenerateCharacterBehaviors.FindOrAdd(CharacterBehaviorCognitionEffect.Key);

				FGeneratedBehaviorCognition NewBehaviorCognition;
				NewBehaviorCognition.CognitionLevelToAwareness.Emplace(Pair.Value, AwarenessTags);
				UngenerateBehavior.DescToCognition.Emplace(Pair.Key, NewBehaviorCognition);
			}
		}
	}
}

const FExperiencedEventInfomation* AMemoryPlayerState::GetExperiencedEventInfomation(FGameplayTag EventStageTag) const
{
	return ExperiencedEventInfomation_AllStage.Find(EventStageTag);
}

const FGeneratedBehavior* AMemoryPlayerState::GetGeneratedBehavior(const FGameplayTag& CharacterTag) const
{
	return GeneratedCharacterBehaviors.Find(CharacterTag);;
}

const TGeneratedCharacterBehaviors& AMemoryPlayerState::GetGeneratedCharacterBehaviors() const
{
	return GeneratedCharacterBehaviors;
}

const TExperiencedEventInfomation_AllStage& AMemoryPlayerState::GetExperiencedEventInfomation_AllStage() const
{
	return ExperiencedEventInfomation_AllStage;
}

USelfAwarenessSet* AMemoryPlayerState::GetSelfAwarenessSet()
{
	if (SelfAwarenessSet == nullptr)
	{
		if (UMemoryGameInstance* MemoryGI = GetGameInstance<UMemoryGameInstance>())
		{
			SelfAwarenessSet = MemoryGI->GetAwarenessSet();
		}
	}

	return SelfAwarenessSet;
}