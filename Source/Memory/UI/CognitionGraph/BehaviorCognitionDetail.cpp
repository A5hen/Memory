// Fill out your copyright notice in the Description page of Project Settings.


#include "BehaviorCognitionDetail.h"
#include "Components/ScrollBox.h"//
#include "Memory/GameInstance/MemoryGameInstance.h"//
#include "Memory/UI/GraphContentWidget.h"//
#include "Memory/Player/Cognition/CharacterCognitionSet.h"//
#include "Memory/MemoryGameplayTag.h"//

void UBehaviorCognitionDetail::UpdateContent(const FContentWidgetInfo& ContentWidgetInfo)
{
	check(Content_BehaviorCognitionClass);

	const FMemoryGameplayTags& GameplayTags = FMemoryGameplayTags::Get();

	UCharacterCognitionSet* CharacterCognitionSet = nullptr;
	if (UMemoryGameInstance* MemoryGI = GetGameInstance<UMemoryGameInstance>())
	{
		CharacterCognitionSet = MemoryGI->GetCharacterCognitionSet();
	}
	if (!CharacterCognitionSet)return;

	for (int32 i = 0; i <= ContentWidgetInfo.CognitionLevel; ++i)
	{
		if (i > CurrentCognitionLevel)
		{
			UGraphContentWidget* Content_BehaviorCognition = CreateWidget<UGraphContentWidget>(this, Content_BehaviorCognitionClass);
			Content_BehaviorCognition->ContentWidgetInfo = ContentWidgetInfo;
			Content_BehaviorCognition->ContentWidgetInfo.CognitionLevel = i;

			CurrentCognitionLevel = i;

			Content_BehaviorCognition->DisplayContent();
			ScrollBox_BehaviorCognition->AddChild(Content_BehaviorCognition);
		}
	}
}