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

void AMemoryPlayerState::GenerateCharacterBehaviorCognition(const FGameplayTag& CharacterTag, const FName& BehaviorDesc, const FGameplayTag& EventTag)
{
	FBehaviorCognitionInfo* OutInfo = nullptr;

	FBehaviorCognitionInfomation& BehaviorCognitionInfomation_Generated = CharacterBehaviorCognitionInfomation_Generated.FindOrAdd(CharacterTag);
	FBehaviorCognitionInfomation* BehaviorCognitionInfomation_Ungenerated = CharacterBehaviorCognitionInfomation_Ungenerated.Find(CharacterTag);

	if (FBehaviorCognitionInfo* Info_Generated = BehaviorCognitionInfomation_Generated.DescToInfo.Find(BehaviorDesc))
	{
		Info_Generated->Source.AddTag(EventTag);

		OutInfo = Info_Generated;
	}

	if (!OutInfo)
	{
		if (FBehaviorCognitionInfo* Info_Ungenerated = BehaviorCognitionInfomation_Ungenerated->DescToInfo.Find(BehaviorDesc))
		{
			Info_Ungenerated->Source.AddTag(EventTag);

			BehaviorCognitionInfomation_Generated.DescToInfo.Emplace(BehaviorDesc, *Info_Ungenerated);

			BehaviorCognitionInfomation_Ungenerated->DescToInfo.Remove(BehaviorDesc);

			OutInfo = Info_Ungenerated;
		}
	}

	if (!OutInfo)
	{
		FBehaviorCognitionInfo NewInfo;
		NewInfo.CurrentCognitionLevel = 0;
		NewInfo.Source.AddTag(EventTag);
		BehaviorCognitionInfomation_Generated.DescToInfo.Emplace(BehaviorDesc, NewInfo);

		OutInfo = &NewInfo;
	}

	OnCharacterBehaviorCognitionInfoGenerated.Broadcast(CharacterTag, *OutInfo);
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

	TMap<FGameplayTag, FBehaviorCognitionInfomation> ChangedCharacterBehaviorCognitionInfomation;

	FSelfAwarenessInfo NewInfo;
	NewInfo.Source.AddTag(EventTag);

	SelfAwarenessInfomation_Single.Emplace(AwarenessTag, NewInfo);

	const FAwarenessInfo* AwarenessInfo_Single = SelfAwarenessSet->GetAwarenessInfo_Single(AwarenessTag);

	FGameplayTagContainer TagContainer_Single;
	TagContainer_Single.AddTag(AwarenessTag);

	HandleSelfAwarenessGeneration(TagContainer_Single, AwarenessInfo_Single, ChangedCharacterBehaviorCognitionInfomation);

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

				HandleSelfAwarenessGeneration(*TagContainerkey, Awareness_Group, ChangedCharacterBehaviorCognitionInfomation);
			}
		}
	}

	if (!ChangedCharacterBehaviorCognitionInfomation.IsEmpty())
	{
		OnCharacterBehaviorCognitionInfomationChanged.Broadcast(ChangedCharacterBehaviorCognitionInfomation);
	}
}

void AMemoryPlayerState::HandleSelfAwarenessGeneration(
	const FGameplayTagContainer& AwarenessTags, const FAwarenessInfo* InAwarenessInfo,
	TMap<FGameplayTag, FBehaviorCognitionInfomation>& ChangedCharacterBehaviorCognitionInfomation)
{
	if (!InAwarenessInfo)return;

	for (const auto& Pair1 : InAwarenessInfo->EffectOnCharacterBehaviorCognition)
	{
		FBehaviorCognitionInfomation* BehaviorCognitionInfomation_Generated = CharacterBehaviorCognitionInfomation_Generated.Find(Pair1.Key);
		FBehaviorCognitionInfomation& BehaviorCognitionInfomation_Ungenerated = CharacterBehaviorCognitionInfomation_Ungenerated.FindOrAdd(Pair1.Key);

		FBehaviorCognitionInfomation& ChangedBehaviorCognitionInfomation = ChangedCharacterBehaviorCognitionInfomation.FindOrAdd(Pair1.Key);

		for (const auto& Pair2 : Pair1.Value.NewCognitionLevel)
		{
			bool bCognitionGenerated = false;

			if (BehaviorCognitionInfomation_Generated)
			{
				if (FBehaviorCognitionInfo* Info_Generated = BehaviorCognitionInfomation_Generated->DescToInfo.Find(Pair2.Key))
				{
					Info_Generated->CognitionLevelToAwareness.Emplace(Pair2.Value, AwarenessTags);

					ChangedBehaviorCognitionInfomation.DescToInfo.Emplace(Pair2.Key, *Info_Generated);

					bCognitionGenerated = true;
				}
			}

			if (!bCognitionGenerated)
			{
				FBehaviorCognitionInfo NewInfo;
				NewInfo.CognitionLevelToAwareness.Emplace(Pair2.Value, AwarenessTags);
				BehaviorCognitionInfomation_Ungenerated.DescToInfo.Emplace(Pair2.Key, NewInfo);
			}
		}
	}
}

const FExperiencedEventInfomation* AMemoryPlayerState::GetExperiencedEventInfomation(EEventStage InEventStage) const
{
	return ExperiencedEventInfomation_Stage.Find(InEventStage);
}

const FBehaviorCognitionInfomation* AMemoryPlayerState::GetBehaviorCognitionInfomation(const FGameplayTag& CharacterTag) const
{
	return CharacterBehaviorCognitionInfomation_Generated.Find(CharacterTag);;
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