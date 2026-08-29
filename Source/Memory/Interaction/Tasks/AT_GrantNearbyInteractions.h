// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "AT_GrantNearbyInteractions.generated.h"

/**
 * 
 */
UCLASS()
class MEMORY_API UAT_GrantNearbyInteractions : public UAbilityTask
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
	static UAT_GrantNearbyInteractions* GrantAbilitiesFromNearbyInteractors(
		UGameplayAbility* OwningAbility, float InteractionScanRange, float InteractionScanRate);

protected:

	virtual void Activate() override;

private:

	virtual void OnDestroy(bool AbilityEnded) override;

	float InteractionScanRange = 100;
	float InteractionScanRate = 0.1f;

	FTimerHandle TimerHandle;

	void QueryInteractables();

	TMap<FObjectKey, FGameplayAbilitySpecHandle> InteractionAbilityCache;
};