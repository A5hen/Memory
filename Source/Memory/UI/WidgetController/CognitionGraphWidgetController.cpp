// Fill out your copyright notice in the Description page of Project Settings.


#include "CognitionGraphWidgetController.h"
#include "Memory/Player/MemoryPlayerState.h"//

void UCognitionGraphWidgetController::BroadcastInitialValues()
{
	if (GetMemoryPS())
	{
		const FBehaviorCognitionInfomation* BehaviorCognitionInfomation = MemoryPS->GetBehaviorCognitionInfomation(SelectedCharacter);
		if (BehaviorCognitionInfomation)
		{
			UpdateCognitionGraph.Broadcast(*BehaviorCognitionInfomation);
		}
	}
}

void UCognitionGraphWidgetController::BindCallBacksToDependencies()
{
}