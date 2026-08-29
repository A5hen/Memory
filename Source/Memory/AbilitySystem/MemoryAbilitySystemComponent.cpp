// Fill out your copyright notice in the Description page of Project Settings.


#include "MemoryAbilitySystemComponent.h"
#include "Memory/MemoryGameplayTag.h"//
#include "Memory/AbilitySystem/Ability/MemoryGameplayAbility.h"
#include "Memory/AbilitySystem/MemoryGlobalAbilitySystem.h"//

void UMemoryAbilitySystemComponent::InitAbilityActorInfo(AActor* InAvatarActor, AActor* InOwnerActor)
{
	Super::InitAbilityActorInfo(InAvatarActor, InOwnerActor);

	if (UMemoryGlobalAbilitySystem* GlobalAbilitySystem = UWorld::GetSubsystem<UMemoryGlobalAbilitySystem>(GetWorld()))
	{
		GlobalAbilitySystem->RegisterASC(this);
	}
}

void UMemoryAbilitySystemComponent::AbilityInputTagPressed(const FGameplayTag& InputTag)
{
	if (InputTag.IsValid())
	{
		InputTag_Pressed = InputTag;

		for (const FGameplayAbilitySpec& Spec : GetActivatableAbilities())
		{
			if (Spec.Ability)
			{
				if (Spec.DynamicAbilityTags.HasTagExact(InputTag))
				{
					InputPressedSpecHandles.AddUnique(Spec.Handle);
					InputHeldSpecHandles.AddUnique(Spec.Handle);
				}
				else
				{
					const UMemoryGameplayAbility* MemoryAbilityCDO = CastChecked<UMemoryGameplayAbility>(Spec.Ability);
					if (MemoryAbilityCDO && MemoryAbilityCDO->GetExtraInputTags().HasTagExact(InputTag))
					{
						ExtraInputSpecHandles.AddUnique(Spec.Handle);
					}
				}
			}
		}
	}
}

void UMemoryAbilitySystemComponent::AbilityInputTagReleased(const FGameplayTag& InputTag)
{
	if (InputTag.IsValid())
	{
		for (const FGameplayAbilitySpec& Spec : GetActivatableAbilities())
		{
			if (Spec.Ability && Spec.DynamicAbilityTags.HasTagExact(InputTag))
			{
				InputReleasedSpecHandles.AddUnique(Spec.Handle);
				InputHeldSpecHandles.Remove(Spec.Handle);
			}
		}
	} 
}

void UMemoryAbilitySystemComponent::ProcessAbilityInput(float DeltaTime, bool bGamePaused)
{
	const FMemoryGameplayTags& GameplayTags = FMemoryGameplayTags::Get();

	if (HasMatchingGameplayTag(GameplayTags.State_Interacting))
	{
		ClearAbilityInput();
		return;
	}

	static TArray<FGameplayAbilitySpecHandle> AbilitiesToActivate;
	AbilitiesToActivate.Reset();

	for(const FGameplayAbilitySpecHandle& SpecHandle : InputHeldSpecHandles)
	{
		if (FGameplayAbilitySpec* Spec = FindAbilitySpecFromHandle(SpecHandle))
		{
			if (Spec->Ability && !Spec->IsActive())
			{
				UMemoryGameplayAbility* MemoryAbilityCDO = CastChecked<UMemoryGameplayAbility>(Spec->Ability);

				if (MemoryAbilityCDO->GetActivationPolicy() == EMemoryAbilityActivationPolicy::WhileInputActive)
				{
					AbilitiesToActivate.AddUnique(SpecHandle);
				}	
			}
		}
	}

	for (const FGameplayAbilitySpecHandle& SpecHandle : ExtraInputSpecHandles)
	{
		if (FGameplayAbilitySpec* Spec = FindAbilitySpecFromHandle(SpecHandle))
		{
			if (Spec->IsActive())
			{
				UMemoryGameplayAbility* MemoryAbilityCDO = CastChecked<UMemoryGameplayAbility>(Spec->Ability);
				if (MemoryAbilityCDO->GetInstancingPolicy() != EGameplayAbilityInstancingPolicy::NonInstanced)
				{
					TArray<UGameplayAbility*> Instances = Spec->GetAbilityInstances();
					for (UGameplayAbility* AbilityInstance : Instances)
					{
						UMemoryGameplayAbility* MemoryAbilityInstance = CastChecked<UMemoryGameplayAbility>(AbilityInstance);

						MemoryAbilityInstance->ExtraInputPressed(InputTag_Pressed);
					}
				}
				
			}
		}
	}

	for (const FGameplayAbilitySpecHandle& SpecHandle : InputPressedSpecHandles)
	{
		if (FGameplayAbilitySpec* Spec = FindAbilitySpecFromHandle(SpecHandle))
		{
			if (Spec->IsActive())
			{
				AbilitySpecInputPressed(*Spec);
			}
			else
			{
				const UMemoryGameplayAbility* MemoryAbilityCDO = CastChecked<UMemoryGameplayAbility>(Spec->Ability);

				if (MemoryAbilityCDO->GetActivationPolicy() == EMemoryAbilityActivationPolicy::OnInputTriggered)
				{
					AbilitiesToActivate.AddUnique(Spec->Handle);
				}
			}
		}
	}

	for(const FGameplayAbilitySpecHandle& SpecHandle : AbilitiesToActivate)
	{
		TryActivateAbility(SpecHandle);
	}

	for (const FGameplayAbilitySpecHandle& SpecHandle : InputReleasedSpecHandles)
	{
		if (FGameplayAbilitySpec* Spec = FindAbilitySpecFromHandle(SpecHandle))
		{
			if (Spec->IsActive())
			{
				AbilitySpecInputReleased(*Spec);
			}
		}
	}

	InputPressedSpecHandles.Reset();
	InputReleasedSpecHandles.Reset();

	ExtraInputSpecHandles.Reset();
}

void UMemoryAbilitySystemComponent::ClearAbilityInput()
{
	InputPressedSpecHandles.Reset();
	InputReleasedSpecHandles.Reset();
	InputHeldSpecHandles.Reset();

	ExtraInputSpecHandles.Reset();
}

void UMemoryAbilitySystemComponent::TryActivateAbilitiesOnSpawn()
{
	ABILITYLIST_SCOPE_LOCK();

	for (const FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		const UMemoryGameplayAbility* MemoryAbilityCDO = CastChecked<UMemoryGameplayAbility>(AbilitySpec.Ability);
		MemoryAbilityCDO->TryActivateAbilityOnSpawn(AbilityActorInfo.Get(), AbilitySpec);
	}
}

void UMemoryAbilitySystemComponent::AbilitySpecInputPressed(FGameplayAbilitySpec& Spec)
{
	Super::AbilitySpecInputPressed(Spec);

	if (Spec.IsActive())
	{
		InvokeReplicatedEvent(EAbilityGenericReplicatedEvent::InputPressed, Spec.Handle, Spec.ActivationInfo.GetActivationPredictionKey());
	}
}

void UMemoryAbilitySystemComponent::AbilitySpecInputReleased(FGameplayAbilitySpec& Spec)
{
	Super::AbilitySpecInputReleased(Spec);

	if (Spec.IsActive())
	{
		InvokeReplicatedEvent(EAbilityGenericReplicatedEvent::InputReleased, Spec.Handle, Spec.ActivationInfo.GetActivationPredictionKey());
	}
}