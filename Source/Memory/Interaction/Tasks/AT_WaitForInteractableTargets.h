// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "Memory/Interaction/InteractionOption.h"//
#include "Memory/Interaction/InteractionQuery.h"//
#include "AT_WaitForInteractableTargets.generated.h"

class IInteractableTarget;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInteractableTargetsChangedEvent, const TArray<FInteractionOption>&, InteractableOptions);

/**
 * 
 */
UCLASS()
class MEMORY_API UAT_WaitForInteractableTargets : public UAbilityTask
{
	GENERATED_BODY()
	
public:

	UPROPERTY(BlueprintAssignable)
	FInteractableTargetsChangedEvent InteractableTargetsChanged;

	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
	static UAT_WaitForInteractableTargets* WaitForInteractableTargets_SingleLineTrace(
		UGameplayAbility* OwningAbility, FInteractionQuery InteractionQuery, float InteractionScanRange = 100, float InteractionScanRate = 0.1f);

protected:

	virtual void Activate() override;

	void UpdateInteractableOptions(const TArray<TScriptInterface<IInteractableTarget>>& InteractableTargets);

private:

	virtual void OnDestroy(bool AbilityEnded) override;

	void TryGetInteractableTarget_LineTraceSingle();

	UPROPERTY()
	FInteractionQuery InteractionQuery;

	float InteractionScanRange = 100;
	float InteractionScanRate = 0.1f;

	FTimerHandle TimerHandle;

	TArray<FInteractionOption> CurrentOptions;
};