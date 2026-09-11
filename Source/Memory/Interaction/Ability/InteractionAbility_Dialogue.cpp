// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionAbility_Dialogue.h"
#include "Memory/Interaction/InteractableTarget.h"//

bool UInteractionAbility_Dialogue::SetParams(const FGameplayEventData& EventData)
{
	InteractableTarget = TScriptInterface<IInteractableTarget>(const_cast<AActor*>(ToRawPtr(EventData.Target)));
	if (InteractableTarget)
	{
		ActorTag = InteractableTarget->GetActorTag();
		CurrentBranchIndex = InteractableTarget->GetDialogueBranchIndex();
		NextSentenceIndex = InteractableTarget->GetDialogueSentenceIndex();

		InteractableTarget->GetDialogueContent(DialogueContent);

		if (FDialogueBranch* DialogueBranch = DialogueContent.DialogueBranches.Find(CurrentBranchIndex))
		{
			if (DialogueBranch->DialogueContent.Num() != 0)
			{
				return true;
			}
		}
	}

	return false;
}

bool UInteractionAbility_Dialogue::UpdateDialogueContent(FText& Sentence, TArray<FText>& Options)
{
	FDialogueBranch* DialogueBranch = DialogueContent.DialogueBranches.Find(CurrentBranchIndex);
	if (DialogueBranch)
	{
		if (NextSentenceIndex >= DialogueBranch->DialogueContent.Num())
		{
			return false;
		}

		Sentence = DialogueBranch->DialogueContent[NextSentenceIndex];

		FDialogueOption* DialogueOption = DialogueBranch->DialogueOptions.Find(NextSentenceIndex);
		if (DialogueOption)
		{
			Options = DialogueOption->Options;
		}

		++NextSentenceIndex;

		return true;
	}

	return false;
}

void UInteractionAbility_Dialogue::ReceiveSelectionResult(const FText& Option)
{
	for (const FDialogueOptionEffect& OptionEffect : DialogueContent.DialogueOptionEffects)
	{
		if (OptionEffect.Option.EqualTo(Option))
		{
			CurrentBranchIndex = OptionEffect.BranchToJump;
			NextSentenceIndex = 0;

			if (InteractableTarget)
			{
				InteractableTarget->SetDialogueBranchIndex(CurrentBranchIndex);
			}

			return;
		}
	}
}

void UInteractionAbility_Dialogue::InterruptDialogue()
{
	bInterrupted = true;

	if (InteractableTarget)
	{
		InteractableTarget->SetDialogueSentenceIndex(NextSentenceIndex - 1);
	}
}