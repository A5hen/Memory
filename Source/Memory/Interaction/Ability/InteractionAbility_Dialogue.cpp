// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionAbility_Dialogue.h"
#include "Memory/Interaction/InteractableTarget.h"//

bool UInteractionAbility_Dialogue::SetParams(const FGameplayEventData& EventData)
{
	/*ActorTag = EventData.TargetTags.GetByIndex(0);

	IInteractableTarget* InteractableTarget = Cast<IInteractableTarget>(EventData.Target);
	if (InteractableTarget)
	{
		InteractableTarget->GetDialogueContent(DialogueContent);

		if (FDialogueBranch* DialogueBranch = DialogueContent.DialogueBranches.Find(CurrentBranchIndex))
		{
			if (DialogueBranch->DialogueContent.Num() != 0)
			{
				return true;
			}
		}
	}*/

	return false;
}

bool UInteractionAbility_Dialogue::UpdateDialogueContent(FText& Sentence, TArray<FText>& Options)
{
	FDialogueBranch* DialogueBranch = DialogueContent.DialogueBranches.Find(CurrentBranchIndex);
	if (DialogueBranch)
	{
		if (CurrentSentenceIndex >= DialogueBranch->DialogueContent.Num())
		{
			return false;
		}

		Sentence = DialogueBranch->DialogueContent[CurrentSentenceIndex];

		FDialogueOption* DialogueOption = DialogueBranch->DialogueOptions.Find(CurrentSentenceIndex);
		if (DialogueOption)
		{
			Options = DialogueOption->Options;
		}

		++CurrentSentenceIndex;

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
			CurrentSentenceIndex = 0;
			return;
		}
	}
}