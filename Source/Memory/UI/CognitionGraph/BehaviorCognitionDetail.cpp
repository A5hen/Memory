// Fill out your copyright notice in the Description page of Project Settings.


#include "BehaviorCognitionDetail.h"
#include "Components/TextBlock.h"//
#include "Components/ScrollBox.h"//
#include "Memory/GameInstance/MemoryGameInstance.h"//
#include "Memory/UI/GraphContentWidget.h"//
#include "Memory/Player/Cognition/CharacterCognitionSet.h"//
#include "Memory/Player/MemoryPlayerState.h"//
#include "Memory/MemoryGameplayTag.h"//

void UBehaviorCognitionDetail::UpdateDetail(const FGameplayTag& InCharacterTag, const FName& InBehaviorDesc, const FGeneratedBehaviorCognition& GeneratedBehaviorCognition)
{
	check(Content_BehaviorCognitionClass);

	if (InCharacterTag.MatchesTagExact(CharacterTag) && InBehaviorDesc.IsEqual(BehaviorDesc))return;

	const FMemoryGameplayTags& GameplayTags = FMemoryGameplayTags::Get();

	UCharacterCognitionSet* CharacterCognitionSet = nullptr;
	if (UMemoryGameInstance* MemoryGI = GetGameInstance<UMemoryGameInstance>())
	{
		CharacterCognitionSet = MemoryGI->GetCharacterCognitionSet();
	}
	if (!CharacterCognitionSet)return;

	CharacterTag = InCharacterTag;
	BehaviorDesc = InBehaviorDesc;
	//TODO: Set Text_BehaviorDesc

	int32 WidgetNum = ScrollBox_BehaviorCognition->GetChildrenCount();

	for (int32 i = GeneratedBehaviorCognition.CurrentCognitionLevel + 1; i < WidgetNum; ++i)
	{
		ScrollBox_BehaviorCognition->GetChildAt(i)->RemoveFromParent();
	}

	TArray<UWidget*> GeneratedWidgets = ScrollBox_BehaviorCognition->GetAllChildren();

	for (int32 i = 0; i <= GeneratedBehaviorCognition.CurrentCognitionLevel; ++i)
	{
		UGraphContentWidget* Content_BehaviorCognition = nullptr;

		if (i < GeneratedWidgets.Num())
		{
			Content_BehaviorCognition = Cast<UGraphContentWidget>(GeneratedWidgets[i]);
		}
		else
		{
			Content_BehaviorCognition = CreateWidget<UGraphContentWidget>(this, Content_BehaviorCognitionClass);
			ScrollBox_BehaviorCognition->AddChild(Content_BehaviorCognition);

			CurrentCognitionLevel = i;
		}

		Content_BehaviorCognition->ContentWidgetInfo.OwnerWidgetTag = GameplayTags.Widget_CharacterCognitionMenu;
		Content_BehaviorCognition->ContentWidgetInfo.ContentTag = GameplayTags.Content_CharacterBehavior;
		Content_BehaviorCognition->ContentWidgetInfo.CharacterTag = InCharacterTag;
		Content_BehaviorCognition->ContentWidgetInfo.BehaviorDesc = InBehaviorDesc;
		Content_BehaviorCognition->ContentWidgetInfo.CognitionLevel = i;

		Content_BehaviorCognition->DisplayContent();
	}
}