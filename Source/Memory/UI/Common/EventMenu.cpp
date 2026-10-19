// Fill out your copyright notice in the Description page of Project Settings.


#include "EventMenu.h"
#include "Input/CommonUIInputTypes.h"//
#include "CommonButtonBase.h"//
#include "Components/ScrollBox.h"//
#include "Components/WidgetSwitcher.h"//
#include "Memory/UI/WidgetController/EventGraphWidgetController.h"//
#include "Memory/UI/EventGraph/EventGraph.h"//
#include "Memory/UI/EventGraph/EventDetail.h"//
#include "Memory/UI/GraphContentWidget.h"//
#include "Memory/AbilitySystem/MemoryAbilitySystemLibrary.h"//
#include "Memory/MemoryGameplayTag.h"//

void UEventMenu::SetWidgetController(UMemoryWidgetController* InWidgetController)
{
	Super::SetWidgetController(InWidgetController);

	if (UEventGraphWidgetController* EventGraphWidgetController = Cast<UEventGraphWidgetController>(WidgetController))
	{
		EventGraphWidgetController->UpdateEventMenu.AddUObject(this, &UEventMenu::UpdateEventMenu);
		EventGraphWidgetController->UpdateEventGraph.AddUObject(this, &UEventMenu::UpdateEventGraph);

		EventGraphWidgetController->BroadcastInitialValues();
	}
}

void UEventMenu::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	FBindUIActionArgs Args_Pressed(FUIActionTag::ConvertChecked(ScaleTag), false,
		FSimpleDelegate::CreateUObject(this, &UEventMenu::StartGraphScale));
	Args_Pressed.KeyEvent = IE_Pressed;

	FBindUIActionArgs Args_Released(FUIActionTag::ConvertChecked(ScaleTag), false,
		FSimpleDelegate::CreateUObject(this, &UEventMenu::EndGraphScale));
	Args_Released.KeyEvent = IE_Released;

	RegisterUIActionBinding(Args_Pressed);
	RegisterUIActionBinding(Args_Released);

	CoreWidgetJumpButton->OnClicked().AddUObject(this, &UEventMenu::JumpToCoreWidget);
}

void UEventMenu::NativeOnActivated()
{
	if (!WidgetController)
	{
		if (UMemoryWidgetController* EventGraphWidgetController = UMemoryAbilitySystemLibrary::GetEventGraphWidgetController(this))
		{
			SetWidgetController(EventGraphWidgetController);
		}
	}

	ReactContentSelection();

	Super::NativeOnActivated();
}

void UEventMenu::NativeOnDeactivated()
{
	bMouseDown = false;

	MouseStartPosition = FVector2D::ZeroVector;
	MouseCurrentPosition = FVector2D::ZeroVector;
	GraphStartTransform = FWidgetTransform();

	bScalable = false;

	Super::NativeOnDeactivated();
}

FReply UEventMenu::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	MouseStartPosition = InGeometry.AbsoluteToLocal(InMouseEvent.GetScreenSpacePosition());
	bMouseDown = true;

	if (CurrentEventGraph)
	{
		GraphStartTransform = CurrentEventGraph->GetRenderTransform();
	}

	return FReply::Handled();
}

FReply UEventMenu::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	bMouseDown = false;

	return FReply::Handled();
}

FReply UEventMenu::NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (bMouseDown)
	{
		MouseCurrentPosition = InGeometry.AbsoluteToLocal(InMouseEvent.GetScreenSpacePosition());

		FVector2D DeltaPosition = (MouseCurrentPosition - MouseStartPosition);

		if (CurrentEventGraph)
		{
			CurrentEventGraph->SetRenderTranslation(GraphStartTransform.Translation + DeltaPosition);
		}
	}

	return FReply::Handled();
}

FReply UEventMenu::NativeOnMouseWheel(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (bScalable)
	{
		float Delta = InMouseEvent.GetWheelDelta();

		if (CurrentEventGraph)
		{
			CurrentEventGraph->ScaleGraph(Delta);
		}
	}

	return FReply::Handled();
}

void UEventMenu::HandleCoreWidgetJump(const FContentWidgetInfo& ContentWidgetInfo)
{
	for (auto& Pair : GeneratedEventGraphs)
	{
		if (Pair.Value->CheckEvent(ContentWidgetInfo.EventTag))
		{
			GraphSwitcher->SetActiveWidget(Pair.Value);

			Pair.Value->JumptoEventGraphNode(ContentWidgetInfo.EventTag);

			return;
		}
	}
}

void UEventMenu::OnContentSelected(const FContentWidgetInfo& ContentWidgetInfo)
{
	Super::OnContentSelected(ContentWidgetInfo);

	ShowDetail();

	EventDetail->UpdateDetail(ContentWidgetInfo);
}

void UEventMenu::UpdateEventMenu(const TMap<FGameplayTag, FExperiencedEventInfomation>& ExperiencedEventInfomation_AllStage)
{
	check(EventGraphClass);

	FGameplayTagContainer NewEventStages;

	for (const auto& Pair : ExperiencedEventInfomation_AllStage)
	{
		if (!CurrentEventStage.IsValid())
		{
			CurrentEventStage = Pair.Key;
		}

		if (UEventGraph* EventGraph = GeneratedEventGraphs.FindRef(Pair.Key).Get())
		{
			EventGraph->UpdateEventGraph(Pair.Value);

			continue;
		}

		GenerateEventGraph(Pair.Key, Pair.Value);

		NewEventStages.AddTag(Pair.Key);
	}

	if (bFirstUpdate)
	{
		if (CurrentEventStage.IsValid())
		{
			if (UEventGraph* EventGraph = GeneratedEventGraphs.FindRef(CurrentEventStage).Get())
			{
				GraphSwitcher->SetActiveWidget(EventGraph);
				CurrentEventGraph = EventGraph;
			}
		}

		bFirstUpdate = false;
	}

	UpdateEventStageSwitcher(NewEventStages);
}

void UEventMenu::GenerateEventGraph(const FGameplayTag& EventStage, const FExperiencedEventInfomation& FExperiencedEventInfomation)
{
	UEventGraph* NewEventGraph = CreateWidget<UEventGraph>(this, EventGraphClass);
	NewEventGraph->UpdateEventGraph(FExperiencedEventInfomation);

	GraphSwitcher->AddChild(NewEventGraph);
	GeneratedEventGraphs.Emplace(EventStage, NewEventGraph);
}

void UEventMenu::UpdateEventGraph(const FGameplayTag& EventStage, const FExperiencedEventInfomation& ExperiencedEventInfomation, bool bNewStage)
{
	if (bNewStage)
	{
		GenerateEventGraph(EventStage, ExperiencedEventInfomation);
	}
	else if (UEventGraph* EventGraph = GeneratedEventGraphs.FindRef(EventStage).Get())
	{
		EventGraph->UpdateEventGraph(ExperiencedEventInfomation);
	}
}

void UEventMenu::UpdateEventStageSwitcher(const FGameplayTagContainer& NewEventStages)
{
	check(OverviewClass_Event);

	const FMemoryGameplayTags& GameplayTags = FMemoryGameplayTags::Get();

	for (const FGameplayTag& EventStage : NewEventStages)
	{
		if (SelectableEventStages.HasTagExact(EventStage))continue;

		UGraphContentWidget* Overview_Event = CreateWidget<UGraphContentWidget>(this, OverviewClass_Event);
		Overview_Event->ContentWidgetInfo.EventStage = EventStage;

		Overview_Event->OnSelected.AddUObject(this, &UEventMenu::OnEventStageSelected);

		Overview_Event->NotifyController(false);
		Overview_Event->DisplayContent();

		ScrollBox_EventStage->AddChild(Overview_Event);
		SelectableEventStages.AddTag(EventStage);
	}
}

void UEventMenu::OnEventStageSelected(const FContentWidgetInfo& ContentWidgetInfo)
{
	if (ContentWidgetInfo.EventStage.MatchesTagExact(CurrentEventStage))return;

	if (UEventGraph* EventGraph = GeneratedEventGraphs.FindRef(ContentWidgetInfo.EventStage).Get())
	{
		GraphSwitcher->SetActiveWidget(EventGraph);
		CurrentEventStage = ContentWidgetInfo.EventStage;
		CurrentEventGraph = EventGraph;
	}
}

void UEventMenu::StartGraphScale()
{
	bScalable = true;
}

void UEventMenu::EndGraphScale()
{
	bScalable = false;
}