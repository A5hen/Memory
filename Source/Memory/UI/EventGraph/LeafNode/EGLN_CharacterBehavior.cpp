// Fill out your copyright notice in the Description page of Project Settings.


#include "EGLN_CharacterBehavior.h"
#include "Components/ScrollBox.h"//
#include "Memory/UI/GraphContentWidget.h"//
#include "Memory/MemoryGameplayTag.h"//

void UEGLN_CharacterBehavior::UpdateContent(const FGameplayTag& EventTag, const TMap<FGameplayTag, TArray<FName>>& CharacterBehavior)
{
	check(OverviewClass_Character);
	check(OverviewClass_CharacterBehavior);

	const FMemoryGameplayTags& GameplayTags = FMemoryGameplayTags::Get();

	if (ScrollBox_Character->GetChildrenCount() <= 0)
	{
		UGraphContentWidget* Overview_AllCharacter = CreateWidget<UGraphContentWidget>(this, OverviewClass_Character);
		Overview_AllCharacter->ContentWidgetInfo.OwnerWidgetTag = GameplayTags.Widget_EventMenu;
		Overview_AllCharacter->ContentWidgetInfo.ContentTag = GameplayTags.Content_Character;
		Overview_AllCharacter->ContentWidgetInfo.EventTag = EventTag;
		Overview_AllCharacter->ContentWidgetInfo.CharacterTag = FGameplayTag();

		Overview_AllCharacter->OnSelected.AddUObject(this, &UEGLN_CharacterBehavior::OnCharacterSelected);
		Overview_AllCharacter->DisplayContent();

		ScrollBox_Character->AddChild(Overview_AllCharacter);
	}

	for (const auto& Pair : CharacterBehavior)
	{
		if (!GeneratedCharacterBehavior.Find(Pair.Key))
		{
			UGraphContentWidget* Overview_Character = CreateWidget<UGraphContentWidget>(this, OverviewClass_Character);
			Overview_Character->ContentWidgetInfo.OwnerWidgetTag = GameplayTags.Widget_EventMenu;
			Overview_Character->ContentWidgetInfo.ContentTag = GameplayTags.Content_Character;
			Overview_Character->ContentWidgetInfo.EventTag = EventTag;
			Overview_Character->ContentWidgetInfo.CharacterTag = Pair.Key;

			Overview_Character->OnSelected.AddUObject(this, &UEGLN_CharacterBehavior::OnCharacterSelected);

			Overview_Character->DisplayContent();

			ScrollBox_Character->AddChild(Overview_Character);

			GeneratedCharacterBehavior.Add(Pair.Key);
		}

		int32 Index = 0;

		TArray<FName>& BehaviorDescs = GeneratedCharacterBehavior[Pair.Key];

		for(const FName& BehaviorDesc: Pair.Value)
		{
			if (BehaviorDescs.Contains(BehaviorDesc))
			{
				++Index;
			}
			else
			{
				UGraphContentWidget* Overview_Behavior = CreateWidget<UGraphContentWidget>(this, OverviewClass_CharacterBehavior);
				Overview_Behavior->ContentWidgetInfo.OwnerWidgetTag = GameplayTags.Widget_EventMenu;
				Overview_Behavior->ContentWidgetInfo.ContentTag = GameplayTags.Content_CharacterBehavior;
				Overview_Behavior->ContentWidgetInfo.EventTag = EventTag;
				Overview_Behavior->ContentWidgetInfo.CharacterTag = Pair.Key;
				Overview_Behavior->ContentWidgetInfo.BehaviorDesc = BehaviorDesc;

				Overview_Behavior->DisplayContent();

				ScrollBox_CharacterBehavior->InsertChildAt(Index, Overview_Behavior);
				++Index;

				BehaviorDescs.Add(BehaviorDesc);
			}
		}
	}
}

void UEGLN_CharacterBehavior::OnCharacterSelected(const FContentWidgetInfo& ContentWidgetInfo)
{
	if (SelectedCharacterTag.MatchesTagExact(ContentWidgetInfo.CharacterTag))return;

	SelectedCharacterTag = ContentWidgetInfo.CharacterTag;

	for (UWidget* Child : ScrollBox_CharacterBehavior->GetAllChildren())
	{
		if (UGraphContentWidget* Overview = Cast<UGraphContentWidget>(Child))
		{
			if (SelectedCharacterTag.IsValid() && Overview->ContentWidgetInfo.CharacterTag != SelectedCharacterTag)
			{
				Overview->SetVisibility(ESlateVisibility::Collapsed);
			}
			else
			{
				Overview->SetVisibility(ESlateVisibility::Visible);
			}
		}
	}
}