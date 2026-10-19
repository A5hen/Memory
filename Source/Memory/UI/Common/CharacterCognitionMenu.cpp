// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterCognitionMenu.h"
#include "Components/ScrollBox.h"//
#include "Components/WidgetSwitcher.h"//
#include "Memory/UI/WidgetController/CognitionGraphWidgetController.h"//
#include "Memory/UI/CognitionGraph/CharacterCognitionGraph.h"//
#include "Memory/UI/CognitionGraph/BehaviorCognitionDetail.h"//
#include "Memory/UI/GraphContentWidget.h"//
#include "Memory/AbilitySystem/MemoryAbilitySystemLibrary.h"//
#include "Memory/MemoryGameplayTag.h"//

void UCharacterCognitionMenu::SetWidgetController(UMemoryWidgetController* InWidgetController)
{
	Super::SetWidgetController(InWidgetController);

	if (UCognitionGraphWidgetController* CognitionGraphWidgetController = Cast<UCognitionGraphWidgetController>(WidgetController))
	{
		CognitionGraphWidgetController->UpdateCognitionMenu.AddUObject(this, &UCharacterCognitionMenu::UpdateCognitionMenu);
		CognitionGraphWidgetController->UpdateCognitionGraph.AddUObject(this, &UCharacterCognitionMenu::UpdateCognitionGraph);

		CognitionGraphWidgetController->BroadcastInitialValues();
	}
}

void UCharacterCognitionMenu::TestJumpFunction()
{
	const FMemoryGameplayTags& GameplayTags = FMemoryGameplayTags::Get();
	PushCoreWidget(GameplayTags.Widget_EventMenu, GameplayTags.Layer_Menu);
}

void UCharacterCognitionMenu::NativeOnActivated()
{
	if (!WidgetController)
	{
		if (UMemoryWidgetController* CognitionGraphWidgetController = UMemoryAbilitySystemLibrary::GetCognitionGraphWidgetController(this))
		{
			SetWidgetController(CognitionGraphWidgetController);
		}
	}

	ReactContentSelection();

	Super::NativeOnActivated();
}

void UCharacterCognitionMenu::NativeOnDeactivated()
{
	bMouseDown = false;

	MouseStartPosition = FVector2D::ZeroVector;
	MouseCurrentPosition = FVector2D::ZeroVector;
	GraphStartTransform = FWidgetTransform();

	Super::NativeOnDeactivated();
}

FReply UCharacterCognitionMenu::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	MouseStartPosition = InGeometry.AbsoluteToLocal(InMouseEvent.GetScreenSpacePosition());
	bMouseDown = true;

	if (CurrentCharacterCognitionGraph)
	{
		GraphStartTransform = CurrentCharacterCognitionGraph->GetRenderTransform();
	}

	return FReply::Handled();
}

FReply UCharacterCognitionMenu::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	bMouseDown = false;

	return FReply::Handled();
}

FReply UCharacterCognitionMenu::NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (bMouseDown)
	{
		MouseCurrentPosition = InGeometry.AbsoluteToLocal(InMouseEvent.GetScreenSpacePosition());

		FVector2D DeltaPosition = (MouseCurrentPosition - MouseStartPosition);

		if (CurrentCharacterCognitionGraph)
		{
			CurrentCharacterCognitionGraph->SetRenderTranslation(GraphStartTransform.Translation + DeltaPosition);
		}
	}

	return FReply::Handled();
}

void UCharacterCognitionMenu::HandleCoreWidgetJump(const FContentWidgetInfo& ContentWidgetInfo)
{
	if (UCharacterCognitionGraph* TargetCognitionGraph = GeneratedCharacterCognitionGraphs.FindRef(ContentWidgetInfo.CharacterTag).Get())
	{
		GraphSwitcher->SetActiveWidget(TargetCognitionGraph);

		TargetCognitionGraph->JumptoCognitionGraphNode(ContentWidgetInfo.BehaviorDesc);
	}
}

void UCharacterCognitionMenu::OnContentSelected(const FContentWidgetInfo& ContentWidgetInfo)
{
	Super::OnContentSelected(ContentWidgetInfo);

	const FMemoryGameplayTags& GameplayTags = FMemoryGameplayTags::Get();

	if (ContentWidgetInfo.ContentTag.MatchesTagExact(GameplayTags.Content_CharacterBehavior))
	{
		ShowDetail();

		if (UCognitionGraphWidgetController* CognitionGraphWidgetController = Cast<UCognitionGraphWidgetController>(WidgetController))
		{
			if (const FGeneratedBehaviorCognition* GenerateBehaviordCognition = CognitionGraphWidgetController->GetGeneratedBehaviorCognition(ContentWidgetInfo.CharacterTag, ContentWidgetInfo.BehaviorDesc))
			{
				BehaviorCognitionDetail->UpdateDetail(ContentWidgetInfo.CharacterTag, ContentWidgetInfo.BehaviorDesc, *GenerateBehaviordCognition);
			}
		}
	}
}

void UCharacterCognitionMenu::UpdateCognitionMenu(const TMap<FGameplayTag, FGeneratedBehavior>& GeneratedCharacterBehaviors)
{
	check(CharacterCognitionGraphClass);

	FGameplayTagContainer NewSelectableCharacters;

	for (const auto& Pair : GeneratedCharacterBehaviors)
	{
		if (!CurrentCharacter.IsValid())
		{
			CurrentCharacter = Pair.Key;
		}

		if (UCharacterCognitionGraph* CharacterCognitionGraph = GeneratedCharacterCognitionGraphs.FindRef(Pair.Key).Get())
		{
			CharacterCognitionGraph->UpdateCognitionGraph(Pair.Value);

			continue;
		}

		GenerateCognitionGraph(Pair.Key, Pair.Value);

		NewSelectableCharacters.AddTag(Pair.Key);
	}

	if (bFirstUpdate)
	{
		if (CurrentCharacter.IsValid())
		{
			if (UCharacterCognitionGraph* CharacterCognitionGraph = GeneratedCharacterCognitionGraphs.FindRef(CurrentCharacter).Get())
			{
				GraphSwitcher->SetActiveWidget(CharacterCognitionGraph);
				CurrentCharacterCognitionGraph = CharacterCognitionGraph;
			}
		}

		bFirstUpdate = false;
	}

	UpdateCharacterSwitcher(NewSelectableCharacters);
}

void UCharacterCognitionMenu::GenerateCognitionGraph(const FGameplayTag& CharacterTag, const FGeneratedBehavior& GeneratedBehavior)
{
	UCharacterCognitionGraph* NewCharacterCognitonGraph = CreateWidget<UCharacterCognitionGraph>(this, CharacterCognitionGraphClass);
	NewCharacterCognitonGraph->SetCharacterTag(CharacterTag);
	NewCharacterCognitonGraph->UpdateCognitionGraph(GeneratedBehavior);

	GraphSwitcher->AddChild(NewCharacterCognitonGraph);
	GeneratedCharacterCognitionGraphs.Emplace(CharacterTag, NewCharacterCognitonGraph);
}

void UCharacterCognitionMenu::UpdateCognitionGraph(const FGameplayTag& CharacterTag, const FGeneratedBehavior& GeneratedBehavior, bool bNewCharacter)
{
	if (bNewCharacter)
	{
		GenerateCognitionGraph(CharacterTag, GeneratedBehavior);
	}
	else if (UCharacterCognitionGraph* CharacterCognitionGraph = GeneratedCharacterCognitionGraphs.FindRef(CharacterTag).Get())
	{
		CharacterCognitionGraph->UpdateCognitionGraph(GeneratedBehavior);
	}
}

void UCharacterCognitionMenu::UpdateCharacterSwitcher(const FGameplayTagContainer& NewSelectableCharacters)
{
	check(OverviewClass_Character);

	const FMemoryGameplayTags& GameplayTags = FMemoryGameplayTags::Get();

	for (const FGameplayTag& CharacterTag : NewSelectableCharacters)
	{
		if (SelectableCharacters.HasTagExact(CharacterTag))continue;

		UGraphContentWidget* Overview_Character = CreateWidget<UGraphContentWidget>(this, OverviewClass_Character);
		Overview_Character->ContentWidgetInfo.CharacterTag = CharacterTag;

		Overview_Character->OnSelected.AddUObject(this, &UCharacterCognitionMenu::OnCharacterSelected);

		Overview_Character->NotifyController(false);
		Overview_Character->DisplayContent();

		ScrollBox_Character->AddChild(Overview_Character);
		SelectableCharacters.AddTag(CharacterTag);
	}
}

void UCharacterCognitionMenu::OnCharacterSelected(const FContentWidgetInfo& ContentWidgetInfo)
{
	if (ContentWidgetInfo.CharacterTag.MatchesTagExact(CurrentCharacter))return;

	if (UCharacterCognitionGraph* CharacterCognitionGraph = GeneratedCharacterCognitionGraphs.FindRef(ContentWidgetInfo.CharacterTag).Get())
	{
		GraphSwitcher->SetActiveWidget(CharacterCognitionGraph);
		CurrentCharacter = ContentWidgetInfo.CharacterTag;
		CurrentCharacterCognitionGraph = CharacterCognitionGraph;
	}
}