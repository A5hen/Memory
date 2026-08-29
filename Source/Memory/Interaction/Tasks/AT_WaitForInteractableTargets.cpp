// Fill out your copyright notice in the Description page of Project Settings.


#include "AT_WaitForInteractableTargets.h"
#include "AbilitySystemComponent.h"//
#include "Memory/Interaction/InteractableTarget.h"//
#include "Memory/Interaction/InteractionQuery.h"
#include "Memory/Interaction/InteractionStatic.h"//
#include "Memory/Memory.h"//

UAT_WaitForInteractableTargets* UAT_WaitForInteractableTargets::WaitForInteractableTargets_SingleLineTrace(
    UGameplayAbility* OwningAbility, FInteractionQuery InteractionQuery, float InteractionScanRange, float InteractionScanRate)
{
    UAT_WaitForInteractableTargets* Task = NewAbilityTask<UAT_WaitForInteractableTargets>(OwningAbility);
    Task->InteractionQuery = InteractionQuery;
    Task->InteractionScanRange = InteractionScanRange;
    Task->InteractionScanRate = InteractionScanRate;
    return Task;
}

void UAT_WaitForInteractableTargets::Activate()
{
    if (UWorld* World = GetWorld())
    {
        World->GetTimerManager().SetTimer(
            TimerHandle, this, &UAT_WaitForInteractableTargets::TryGetInteractableTarget_LineTraceSingle, InteractionScanRate, true);
    }
}

void UAT_WaitForInteractableTargets::UpdateInteractableOptions(const TArray<TScriptInterface<IInteractableTarget>>& InteractableTargets)
{
    TArray<FInteractionOption> NewOptions;

    for (const TScriptInterface<IInteractableTarget>& InteractiveTarget : InteractableTargets)
    {
        TArray<FInteractionOption> TempOptions;
        FInteractionOptionBuilder InteractionBuilder(InteractiveTarget, TempOptions);
        InteractiveTarget->GatherInteractionOptions(InteractionQuery, InteractionBuilder);

        for (FInteractionOption& Option : TempOptions)
        {
            FGameplayAbilitySpec* InteractionAbilitySpec = nullptr;

            // if there is a handle an a target ability system, we're triggering the ability on the target.
            if (Option.TargetAbilitySystem && Option.TargetInteractionAbilityHandle.IsValid())
            {
                // Find the spec
                InteractionAbilitySpec = Option.TargetAbilitySystem->FindAbilitySpecFromHandle(Option.TargetInteractionAbilityHandle);
            }
            // If there's an interaction ability then we're activating it on ourselves.
            else if (Option.InteractionAbilityToGrant)
            {
                // Find the spec
                InteractionAbilitySpec = AbilitySystemComponent->FindAbilitySpecFromClass(Option.InteractionAbilityToGrant);
                if (InteractionAbilitySpec)
                {
                    // update the option
                    Option.TargetAbilitySystem = AbilitySystemComponent.Get();
                    Option.TargetInteractionAbilityHandle = InteractionAbilitySpec->Handle;
                }
            }

            if (InteractionAbilitySpec)
            {
                // Filter any options that we can't activate right now for whatever reason.
                if (InteractionAbilitySpec->Ability->CanActivateAbility(InteractionAbilitySpec->Handle, AbilitySystemComponent->AbilityActorInfo.Get()))
                {
                    NewOptions.Add(Option);
                }
            }
        }
    }

    bool bOptionsChanged = false;
    if (NewOptions.Num() == CurrentOptions.Num())
    {
        NewOptions.Sort();

        for (int OptionIndex = 0; OptionIndex < NewOptions.Num(); OptionIndex++)
        {
            const FInteractionOption& NewOption = NewOptions[OptionIndex];
            const FInteractionOption& CurrentOption = CurrentOptions[OptionIndex];

            if (NewOption != CurrentOption)
            {
                bOptionsChanged = true;
                break;
            }
        }
    }
    else
    {
        bOptionsChanged = true;
    }

    if (bOptionsChanged)
    {
        CurrentOptions = NewOptions;
        InteractableTargetsChanged.Broadcast(CurrentOptions);
    }
}

void UAT_WaitForInteractableTargets::OnDestroy(bool AbilityEnded)
{
    if (UWorld* World = GetWorld())
    {
        World->GetTimerManager().ClearTimer(TimerHandle);
    }

    Super::OnDestroy(AbilityEnded);
}

void UAT_WaitForInteractableTargets::TryGetInteractableTarget_LineTraceSingle()
{
    UWorld* World = GetWorld();
    AActor* AvatarActor = Ability->GetCurrentActorInfo()->AvatarActor.Get();
    APlayerController* PlayerController = Ability->GetCurrentActorInfo()->PlayerController.Get();

    if (!World || !AvatarActor || !PlayerController)return;

    TArray<AActor*>ActorsToIgnore;
    ActorsToIgnore.Add(AvatarActor);

    FCollisionQueryParams Params;
    Params.AddIgnoredActors(ActorsToIgnore);

    FVector ViewStart;
    FRotator ViewRot;
    PlayerController->GetPlayerViewPoint(ViewStart, ViewRot);

    FVector ViewEnd = ViewStart + (ViewRot.Vector() * InteractionScanRange);

    FHitResult OutHitResult;
    World->LineTraceSingleByChannel(OutHitResult, ViewStart, ViewEnd, ECC_Interaction, Params);

    TArray<TScriptInterface<IInteractableTarget>> InteractableTargets;
    UInteractionStatic::AppendInteractableTargetsFromHitResult(OutHitResult, InteractableTargets);

    UpdateInteractableOptions(InteractableTargets);

    if (OutHitResult.bBlockingHit)
    {
        DrawDebugLine(World, ViewStart, OutHitResult.Location, FColor::Red, false, InteractionScanRate);
        DrawDebugSphere(World, OutHitResult.Location, 5, 16, FColor::Red, false, InteractionScanRate);
    }
    else
    {
        DrawDebugLine(World, ViewStart, ViewEnd, FColor::Blue, false, InteractionScanRate);
    }
}