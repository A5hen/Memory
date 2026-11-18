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

	const FMemoryGameplayTags& GameplayTags = FMemoryGameplayTags::Get();

	UCharacterCognitionSet* CharacterCognitionSet = nullptr;
	if (UMemoryGameInstance* MemoryGI = GetGameInstance<UMemoryGameInstance>())
	{
		CharacterCognitionSet = MemoryGI->GetCharacterCognitionSet();
	}
	if (!CharacterCognitionSet)return;

	bool bIncrementalUpdate = true;
	if (InCharacterTag != CharacterTag || InBehaviorDesc != BehaviorDesc)
	{
		bIncrementalUpdate = false;
	}
	else if (CurrentCognitionLevel == GeneratedBehaviorCognition.CurrentCognitionLevel)
	{
		return;
	}

	CharacterTag = InCharacterTag;
	BehaviorDesc = InBehaviorDesc;

	Text_BehaviorDesc->SetText(FText::FromName(BehaviorDesc));

	int32 StartIndex = 0;

	if (!bIncrementalUpdate)
	{
		for (int32 i = GeneratedBehaviorCognition.CurrentCognitionLevel + 1; i <= CurrentCognitionLevel; ++i)
		{
			ScrollBox_BehaviorCognition->GetChildAt(i)->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
	else
	{
		StartIndex = CurrentCognitionLevel + 1;
	}

	TArray<UWidget*> GeneratedWidgets = ScrollBox_BehaviorCognition->GetAllChildren();

	for (int32 i = StartIndex; i <= GeneratedBehaviorCognition.CurrentCognitionLevel; ++i)
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

		Content_BehaviorCognition->SetVisibility(ESlateVisibility::Visible);

		Content_BehaviorCognition->ContentWidgetInfo.OwnerWidgetTag = GameplayTags.Widget_CharacterCognitionMenu;
		Content_BehaviorCognition->ContentWidgetInfo.ContentTag = GameplayTags.Content_CharacterBehavior;
		Content_BehaviorCognition->ContentWidgetInfo.CharacterTag = InCharacterTag;
		Content_BehaviorCognition->ContentWidgetInfo.BehaviorDesc = InBehaviorDesc;
		Content_BehaviorCognition->ContentWidgetInfo.CognitionLevel = i;

		Content_BehaviorCognition->UpdateContent();
	}
}