// Fill out your copyright notice in the Description page of Project Settings.


#include "EventGraphWidgetController.h"
#include "Memory/Player/MemoryPlayerState.h"//

void UEventGraphWidgetController::BroadcastInitialValues()
{
	if (GetMemoryPS())
	{
		const TMap<EEventStage, FExperiencedEventInfomation>& ExperiencedEventInfomation_AllStage = MemoryPS->GetExperiencedEventInfomation_AllStage();
		UpdateEventMenu.Broadcast(ExperiencedEventInfomation_AllStage);
	}
}

void UEventGraphWidgetController::BindCallBacksToDependencies()
{
}