#pragma once


#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"//
#include "InteractionOption.generated.h"

class IInteractableTarget;
class UUserWidget;

USTRUCT(BlueprintType)
struct FInteractionOption
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Option;

	UPROPERTY(BlueprintReadWrite)
	TScriptInterface<IInteractableTarget> InteractableTarget;

	//(1) Place an ability on the avatar that they can activate when they perform interaction.

	/*The ability to grant the avatar when they get near interactable objects*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UGameplayAbility> InteractionAbilityToGrant;

	//(2) Allow the object we're interacting with to have its own ability system and interaction ability, that we can activate instead.

	/*The ability system on the target that can be used for the TargetInteractionHandle and sending the event, if needed*/

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UAbilitySystemComponent> TargetAbilitySystem = nullptr;

	/** The ability spec to activate on the object for this option. */
	UPROPERTY(BlueprintReadOnly)
	FGameplayAbilitySpecHandle TargetInteractionAbilityHandle;

public:

	FORCEINLINE bool operator==(const FInteractionOption& Other) const
	{
		return Option.IdenticalTo(Other.Option) &&
			InteractableTarget == Other.InteractableTarget &&
			InteractionAbilityToGrant == Other.InteractionAbilityToGrant &&
			TargetAbilitySystem == Other.TargetAbilitySystem &&
			TargetInteractionAbilityHandle == Other.TargetInteractionAbilityHandle;
	}

	FORCEINLINE bool operator!=(const FInteractionOption& Other) const
	{
		return !operator==(Other);
	}

	FORCEINLINE bool operator<(const FInteractionOption& Other) const
	{
		return InteractableTarget.GetInterface() < Other.InteractableTarget.GetInterface();
	}
};