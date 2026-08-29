// Fill out your copyright notice in the Description page of Project Settings.


#include "EventGraphWidgetController.h"
#include "Memory/Player/MemoryPlayerState.h"//

void UEventGraphWidgetController::BroadcastInitialValues()
{
	if (GetMemoryPS())
	{
		const FExperiencedEventInfomation* ExperiencedEventInfomation = MemoryPS->GetExperiencedEventInfomation(EventStage_Graph);
		if (ExperiencedEventInfomation)
		{
			UpdateEventGraph.Broadcast(*ExperiencedEventInfomation);
		}	
	}
}

void UEventGraphWidgetController::BindCallBacksToDependencies()
{
}

void UEventGraphWidgetController::RecordGraphTransform_Stage(const FVector2D& Offset, float Scale)
{
	FGraphTransform NewTransform;
	NewTransform.GraphOffset = Offset;
	NewTransform.GraphScale = Scale;

	GraphTransform_Stage.Emplace(CurrentEventStage, NewTransform);
}

const FGraphTransform* UEventGraphWidgetController::GetGraphTransform_Stage(EEventStage InEventStage)
{
	return GraphTransform_Stage.Find(InEventStage);;
}

void UEventGraphWidgetController::SwitchEventStage(EEventStage TargetEventStage)
{
	EventStage_Graph = TargetEventStage;

	BroadcastInitialValues();
}