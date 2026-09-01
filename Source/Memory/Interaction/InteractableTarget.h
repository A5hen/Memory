// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GameplayTagContainer.h"//
#include "Memory/Interaction/InteractionOption.h"//
#include "Memory/Memory.h"//
#include "InteractableTarget.generated.h"

USTRUCT(BlueprintType)
struct FDialogueOptionEffect
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Option;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 BranchToJump = -1;
};

USTRUCT(BlueprintType)
struct FDialogueOption
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FText> Options;
};

USTRUCT(BlueprintType)
struct FDialogueBranch
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FText> DialogueContent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<int32, FDialogueOption> DialogueOptions;
};

USTRUCT(BlueprintType)
struct FDialogueContent
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<int32, FDialogueBranch> DialogueBranches;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FDialogueOptionEffect> DialogueOptionEffects;
};

struct FInteractionOption;
struct FInteractionQuery;

class FInteractionOptionBuilder
{
public:

	FInteractionOptionBuilder(TScriptInterface<IInteractableTarget> InterfaceTargetScope, TArray<FInteractionOption>& InteractOptions)
		: Scope(InterfaceTargetScope)
		, Options(InteractOptions)
	{
	}

	void AddInteractionOption(const FInteractionOption& Option)
	{
		FInteractionOption& OptionEntry = Options.Add_GetRef(Option);
		OptionEntry.InteractableTarget = Scope;
	}

private:

	TScriptInterface<IInteractableTarget> Scope;
	TArray<FInteractionOption>& Options;
};

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInteractableTarget : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MEMORY_API IInteractableTarget
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual void GatherInteractionOptions(const FInteractionQuery& InteractQuery, FInteractionOptionBuilder& OptionBuilder) = 0;

	virtual void ShowOption(const FText& Option, bool bShow) {}
	virtual void SelectOption(const FText& Option, bool bSelect) {}

	virtual bool IsInteractable() const { return true; }

	virtual FGameplayTag GetActorTag() const { return FGameplayTag(); }

	/*Character*/
	virtual void GetDialogueContent(FDialogueContent& OutDialogueContent) const {}

	virtual void SetDialogueContent(const FDialogueContent& NewDialogueContent) {}

	virtual void CharacterMove(AActor* TargetPoint) {}
	/*Character*/
};