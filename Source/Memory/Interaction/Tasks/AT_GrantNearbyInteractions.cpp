// Fill out your copyright notice in the Description page of Project Settings.


#include "AT_GrantNearbyInteractions.h"
#include "AbilitySystemComponent.h"//
#include "Memory/Interaction/InteractableTarget.h"//
#include "Memory/Interaction/InteractionOption.h"//
#include "Memory/Interaction/InteractionQuery.h"//
#include "Memory/Interaction/InteractionStatic.h"//
#include "Memory/Memory.h"//

UAT_GrantNearbyInteractions* UAT_GrantNearbyInteractions::GrantAbilitiesFromNearbyInteractors(UGameplayAbility* OwningAbility, float InteractionScanRange, float InteractionScanRate)
{
	UAT_GrantNearbyInteractions* Task = NewAbilityTask<UAT_GrantNearbyInteractions>(OwningAbility);
	Task->InteractionScanRange = InteractionScanRange;
	Task->InteractionScanRate = InteractionScanRate;
	return Task;
}

void UAT_GrantNearbyInteractions::Activate()
{
	if(UWorld* World = GetWorld())
	{
		World->GetTimerManager().SetTimer(TimerHandle, this, &UAT_GrantNearbyInteractions::QueryInteractables, InteractionScanRate, true);
	}
}

void UAT_GrantNearbyInteractions::OnDestroy(bool AbilityEnded)
{
	if (UWorld* World = GetWorld())
	{
		World->GetTimerManager().ClearTimer(TimerHandle);
	}

	Super::OnDestroy(AbilityEnded);
}

void UAT_GrantNearbyInteractions::QueryInteractables()
{
	UWorld* World = GetWorld();
	AActor* AvatarActor = GetAvatarActor();

	if (World && AvatarActor)
	{
		TArray<FOverlapResult> OverlapResults;
		FCollisionQueryParams Params;

		World->OverlapMultiByChannel(
			OverlapResults, AvatarActor->GetActorLocation(), FQuat::Identity, ECC_Interaction, FCollisionShape::MakeSphere(InteractionScanRange), Params);

		if (OverlapResults.Num() > 0)
		{
			TArray<TScriptInterface<IInteractableTarget>> InteractableTargets;
			UInteractionStatic::AppendInteractableTargetsFromOverlapResults(OverlapResults, InteractableTargets);

			FInteractionQuery InteractionQuery;
			InteractionQuery.RequestingAvatar = AvatarActor;
			InteractionQuery.RequestingController = Cast<AController>(AvatarActor->GetOwner());

			TArray<FInteractionOption> Options;
			for (TScriptInterface<IInteractableTarget>& InteractiveTarget : InteractableTargets)
			{
				FInteractionOptionBuilder InteractionBuilder(InteractiveTarget, Options);
				InteractiveTarget->GatherInteractionOptions(InteractionQuery, InteractionBuilder);
			}

			// Check if any of the options need to grant the ability to the user before they can be used.
			for (FInteractionOption& Option : Options)
			{
				if (Option.InteractionAbilityToGrant)
				{
					// Grant the ability to the GAS, otherwise it won't be able to do whatever the interaction is.
					FObjectKey ObjectKey(Option.InteractionAbilityToGrant);
					if (!InteractionAbilityCache.Find(ObjectKey))
					{
						FGameplayAbilitySpec Spec(Option.InteractionAbilityToGrant, 1, INDEX_NONE, this);
						FGameplayAbilitySpecHandle Handle = AbilitySystemComponent->GiveAbility(Spec);
						InteractionAbilityCache.Add(ObjectKey, Handle);
					}
				}
			}
		}
	}
}