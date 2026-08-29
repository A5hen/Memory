// Fill out your copyright notice in the Description page of Project Settings.


#include "EventMenu.h"
#include "Components/SizeBox.h"//
#include "Components/CanvasPanelSlot.h"//
#include "Blueprint/WidgetLayoutLibrary.h"//
#include "Input/CommonUIInputTypes.h"//
#include "CommonButtonBase.h"//
#include "Memory/UI/WidgetController/EventGraphWidgetController.h"//
#include "Memory/UI/EventGraph/EventGraph.h"//
#include "Memory/AbilitySystem/MemoryAbilitySystemLibrary.h"//

void UEventMenu::SetWidgetController(UMemoryWidgetController* InWidgetController)
{
	Super::SetWidgetController(InWidgetController);

	if (WidgetController)
	{
		EventGraph->SetWidgetController(WidgetController);
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
	else
	{

	}

	ReactContentSelection();

	Super::NativeOnActivated();
}

void UEventMenu::NativeOnDeactivated()
{
	EventGraph->UnbindCallBacks();

	bMouseDown = false;

	MousePosition = FVector2D::ZeroVector;
	MousePositionLastFrame = FVector2D::ZeroVector;

	bScalable = false;

	Super::NativeOnDeactivated();
}

FReply UEventMenu::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	MousePosition = InMouseEvent.GetScreenSpacePosition();
	bMouseDown = true;

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
		MousePositionLastFrame = MousePosition;
		MousePosition = InMouseEvent.GetScreenSpacePosition();

		FVector2D DeltaPosition = (MousePosition - MousePositionLastFrame);

		FWidgetTransform NewTransform = EventGraph->GetRelativeTransform();
		NewTransform.Translation += DeltaPosition;

		GraphOffset += DeltaPosition;

		EventGraph->SetRelativeTransform(NewTransform);
	}

	return FReply::Handled();
}

FReply UEventMenu::NativeOnMouseWheel(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (bScalable)
	{
		float WheelData = InMouseEvent.GetWheelDelta();

		if (WheelData < 0)
		{
			GraphScale = FMath::Max(0.5f, GraphScale - 0.1);
		}
		else
		{
			GraphScale = FMath::Min(1.f, GraphScale + 0.1);
		}

		EventGraph->SetRenderScale(FVector2D(GraphScale, GraphScale));
	}

	return FReply::Handled();
}

void UEventMenu::OnContentSelected(const FContentWidgetInfo& ContentWidgetInfo)
{
	Super::OnContentSelected(ContentWidgetInfo);

	ShowDetail();
}

void UEventMenu::UpdateEventStageSwitcher(EEventStage CurrentEventStage)
{
}

void UEventMenu::OnEventStageSelected(EEventStage TargetStage)
{
	bScalable = false;

	if (WidgetController)
	{
		if(UEventGraphWidgetController* EventGraphWidgetController = Cast<UEventGraphWidgetController>(WidgetController))
		{
			EventGraph->ClearGraph();

			GraphOffset = FVector2D(0.f, 0.f);
			GraphScale = 1.f;

			EventGraphWidgetController->RecordGraphTransform_Stage(GraphOffset, GraphScale);
			const FGraphTransform* GraphTransform = EventGraphWidgetController->GetGraphTransform_Stage(TargetStage);
			if (GraphTransform)
			{
				GraphOffset = GraphTransform->GraphOffset;
				GraphScale = GraphTransform->GraphScale;
			}

			FWidgetTransform NewTransform = EventGraph->GetRelativeTransform();
			NewTransform.Translation = GraphOffset;
			EventGraph->SetRelativeTransform(NewTransform);

			EventGraph->SetRenderScale(FVector2D(GraphScale, GraphScale));

			EventGraphWidgetController->SwitchEventStage(TargetStage);
		}
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