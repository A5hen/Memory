// Fill out your copyright notice in the Description page of Project Settings.


#include "MemoryGameplayAbility_Interact.h"
#include "AbilitySystemComponent.h"//
#include "Memory/Interaction/Tasks/AT_GrantNearbyInteractions.h"//
#include "Memory/Interaction/InteractableTarget.h"//
#include "Memory/Interaction/InteractionStatic.h"
#include "Memory/MemoryGameplayTag.h"//

void UMemoryGameplayAbility_Interact::ExtraInputPressed(const FGameplayTag& ExtraInputTag)
{
	const FMemoryGameplayTags& GameplayTags = FMemoryGameplayTags::Get();

	if (SelectedIndex == -1 || Options.Num() < 2)return;

	SelectOption_Check(Options[SelectedIndex], false);

	if (ExtraInputTag.MatchesTagExact(GameplayTags.Ability_Extra_Up))
	{
		if (SelectedIndex == 0)return;
		
		SelectedIndex = FMath::Max(0, SelectedIndex - 1);
	}
	else if (ExtraInputTag.MatchesTagExact(GameplayTags.Ability_Extra_Down))
	{
		if (SelectedIndex == Options.Num() - 1)return;

		SelectedIndex = FMath::Max(Options.Num() - 1, SelectedIndex + 1);
	}

	SelectOption_Check(Options[SelectedIndex], true);
}

void UMemoryGameplayAbility_Interact::ActivateAbility(
	const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	UAT_GrantNearbyInteractions* Task = UAT_GrantNearbyInteractions::GrantAbilitiesFromNearbyInteractors(
		this, InteractionScanRange, InteractionScanRate);
	Task->ReadyForActivation();
}

void UMemoryGameplayAbility_Interact::UpdateInteractions(const TArray<FInteractionOption>& InteractiveOptions)
{
	if (SelectedIndex != -1)
	{
		if (!InteractiveOptions.Contains(Options[SelectedIndex]))
		{
			SelectOption_Check(Options[SelectedIndex], false);
			SelectedIndex = -1;
		}
		else
		{
			SelectedIndex = InteractiveOptions.Find(Options[SelectedIndex]);
		}
	}

	for (const FInteractionOption& Option : InteractiveOptions)
	{
		if (!Options.Contains(Option))
		{
			DisplayOption_Check(Option, true);
			Options.Remove(Option);
		}
	}

	for (const FInteractionOption& Option : Options)
	{
		DisplayOption_Check(Option, false);
	}

	Options = InteractiveOptions;

	if (SelectedIndex == -1 && Options.Num() != 0)
	{
		SelectedIndex = 0;
	}

	if (SelectedIndex != -1)
	{
		SelectOption_Check(Options[SelectedIndex], true);
	}
}

void UMemoryGameplayAbility_Interact::TriggerInteraction()
{
	if (Options.Num() == 0)
	{
		return;
	}

	UAbilitySystemComponent* AbilitySystem = GetAbilitySystemComponentFromActorInfo();
	if (AbilitySystem)
	{
		const FInteractionOption& InteractionOption = Options[SelectedIndex];

		AActor* Instigator = GetAvatarActorFromActorInfo();
		AActor* InteractableTargetActor = UInteractionStatic::GetActorFromInteractableTarget(InteractionOption.InteractableTarget);

		FGameplayEventData Payload;
		Payload.Instigator = Instigator;
		Payload.Target = InteractableTargetActor;

		// Grab the target actor off the payload we're going to use it as the 'avatar' for the interaction, and the
		// source InteractableTarget actor as the owner actor.
		AActor* TargetActor = const_cast<AActor*>(ToRawPtr(Payload.Target));

		// The actor info needed for the interaction.
		FGameplayAbilityActorInfo ActorInfo;
		ActorInfo.InitFromActor(InteractableTargetActor, TargetActor, InteractionOption.TargetAbilitySystem);

		// Trigger the ability using event tag.
		InteractionOption.TargetAbilitySystem->TriggerAbilityFromGameplayEvent(
			InteractionOption.TargetInteractionAbilityHandle,
			&ActorInfo,
			FGameplayTag(),
			&Payload,
			*InteractionOption.TargetAbilitySystem);
	}
}

void UMemoryGameplayAbility_Interact::DisplayOption_Check(const FInteractionOption& Option, bool bDisplay)
{
	if (Option.InteractableTarget)
	{
		Option.InteractableTarget->DisplayOption(Option.ID, bDisplay);
	}
}

void UMemoryGameplayAbility_Interact::SelectOption_Check(const FInteractionOption& Option, bool bSelect)
{
	if (Option.InteractableTarget)
	{
		Option.InteractableTarget->SelectOption(Option.ID, bSelect);
	}
}