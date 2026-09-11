// Fill out your copyright notice in the Description page of Project Settings.


#include "MemoryEventDefinition.h"
#include "Memory/GameMode/SpawnPointSubsystem.h"//
#include "Memory/GameMode/SpawnPoint.h"//
#include "Memory/GameMode/EventAsyncAction.h"//
#include "Memory/AbilitySystem/MemoryGlobalAbilitySystem.h"//
#include "Memory/Interaction/InteractableTarget.h"//
#include "Memory/Player/MemoryPlayerState.h"//
#include "Memory/Player/PlayerControllerInterface.h"//
#include "Memory/UI/Common/MemoryActivatableWidget.h"//
#include "Memory/UI/Common/CommonUIExtension.h"//
#include "Memory/UI/Common/CommonUIInterface.h"//
#include "Memory/MemoryGameplayTag.h"//

void UMemoryEventDefinition::FinishEventStep(int32 StepIndex)
{
	OnEventStepFinished.Broadcast(StepIndex);
}

void UMemoryEventDefinition::SetOutterWorldContext(UWorld* OutterWorldContext)
{
	WorldContext = OutterWorldContext;
}

void UMemoryEventDefinition::SetPlayerController(APlayerController* InPlayerController)
{
	PlayerController = InPlayerController;
}

void UMemoryEventDefinition::RegisterEventAsyncAction(UEventAsyncAction* ActionToActivate)
{
	const FName& ActionName = ActionToActivate->GetActionName();
	EActionType ActionType = ActionToActivate->GetActionType();
	
	if (CheckActionIsFinished(ActionName))
	{
		ActionToActivate->ActivateNextAsyncAction();
		ActionToActivate->Destory();
		return;
	}
	
	const FGameplayTag& ActorTag = ActionToActivate->GetActorTag();

	bool bActivated = false;

	FTypeToAsyncAction& TypeToAsyncAction_Active = ActiveEventAsyncActions.FindOrAdd(ActorTag);
	if (!TypeToAsyncAction_Active.TypeToAsyncAction.Contains(ActionType))
	{
		TypeToAsyncAction_Active.TypeToAsyncAction.Emplace(ActionType, ActionToActivate);

		if (ActionToActivate->CheckStartCondition(FinishedActions))
		{
			ActionToActivate->Start();
			bActivated = true;
		}	
	}

	if (!bActivated)
	{
		InactiveEventAsyncActions.Emplace(ActionName, ActionToActivate);
	}
}

void UMemoryEventDefinition::FinishEventAsyncAction(const FGameplayTag& ActorTag, EActionType ActionType)
{
	if (FTypeToAsyncAction* TypeToAsyncAction_Active = ActiveEventAsyncActions.Find(ActorTag))
	{
		bool bAllFinished = true;

		UEventAsyncAction* TargetAsyncAction = nullptr;

		for (const auto& Pair : TypeToAsyncAction_Active->TypeToAsyncAction)
		{
			if (Pair.Key == ActionType)
			{
				TargetAsyncAction = Pair.Value;
			}
			else
			{
				if (!Pair.Value->IsFinished())
				{
					bAllFinished = false;
				}
			}	
		}

		if (!TargetAsyncAction)return;

		TargetAsyncAction->Finish();

		if (bAllFinished)
		{
			for (const auto& Pair : TypeToAsyncAction_Active->TypeToAsyncAction)
			{
				Pair.Value->ActivateNextAsyncAction();
				Pair.Value->Destory();
			}

			TypeToAsyncAction_Active->TypeToAsyncAction.Empty();
		}

		FinishedActions.Add(TargetAsyncAction->GetActionName());

		PostFinishedActionsChange();
	}
}

void UMemoryEventDefinition::PostFinishedActionsChange()
{
	for (auto& Pair : InactiveEventAsyncActions)
	{
		if (Pair.Value->CheckStartCondition(FinishedActions))
		{
			EActionType ActionType = Pair.Value->GetActionType();
			const FGameplayTag& ActorTag = Pair.Value->GetActorTag();

			if (FTypeToAsyncAction* TypeToAsyncAction_Active = ActiveEventAsyncActions.Find(ActorTag))
			{
				if (!TypeToAsyncAction_Active->TypeToAsyncAction.Contains(ActionType))
				{
					TypeToAsyncAction_Active->TypeToAsyncAction.Emplace(ActionType, Pair.Value);
					InactiveEventAsyncActions.Remove(Pair.Key);
					Pair.Value->Start();
				}
			}
		}
	}
}

void UMemoryEventDefinition::SceneSetup()
{
	check(WorldContext);

	if (!GetSpawnPointSubsystem())return;

	for (const auto& Pair : SceneActorClass)
	{
		if (AActor* SpawnPoints = SpawnPointSubsystem->GetSpawnPointByTag(Pair.Key))
		{
			const FTransform& ActorTransform = SpawnPoints->GetActorTransform();

			AActor* Actor = WorldContext->SpawnActor<AActor>(Pair.Value, ActorTransform);

			SceneActors.Emplace(Pair.Key, Actor);
		}
	}
}

bool UMemoryEventDefinition::CheckActionIsFinished(const FName& ActionName) const
{
	for (const FName& FinishedAction : FinishedActions)
	{
		if (FinishedAction == ActionName)
		{
			return true;
		}
	}

	return false;
}

void UMemoryEventDefinition::SendDialogueResult(const FGameplayTag& ActorTag, int32 SentenceIndex, FText Result)
{
	if (FTypeToAsyncAction* TypeToAsyncAction_Active = ActiveEventAsyncActions.Find(ActorTag))
	{
		if (TypeToAsyncAction_Active->TypeToAsyncAction.Contains(EActionType::Dialogue))
		{
			if (UEventAsyncAction* AsyncAction_Dialogue = TypeToAsyncAction_Active->TypeToAsyncAction[EActionType::Dialogue])
			{
				AsyncAction_Dialogue->SendDialogueResult(SentenceIndex, Result);
			}
		}
	}
}

void UMemoryEventDefinition::ClearSceneActor()
{
	for (auto& Pair : SceneActors)
	{
		Pair.Value->Destroy();
	}

	SceneActors.Empty();
}

AActor* UMemoryEventDefinition::GetSceneActorByActorTag(const FGameplayTag& ActorTag) const
{
	for (auto& Pair : SceneActors)
	{
		if (IInteractableTarget* InteractableTarget = Cast<IInteractableTarget>(Pair.Value))
		{
			FGameplayTag SceneActorTag = InteractableTarget->GetActorTag();
			if (SceneActorTag.MatchesTagExact(ActorTag))
			{
				return Pair.Value;
			}
		}
	}

	return nullptr;
}

void UMemoryEventDefinition::PushSelectionWidget(TSubclassOf<UMemoryActivatableWidget> SelectionWidgetClass, FGameplayTag ActorTag, const TArray<FText>& Content)
{
	const FMemoryGameplayTags& GameplayTags = FMemoryGameplayTags::Get();

	if (SelectionWidgetClass && PlayerController)
	{
		UMemoryActivatableWidget* SelectionWidget = UCommonUIExtension::PushContentToLayerForPlayer(PlayerController, GameplayTags.Layer_Selection, SelectionWidgetClass);
		if (ICommonUIInterface* CommonUIInterface = Cast<ICommonUIInterface>(SelectionWidget))
		{
			CommonUIInterface->SetOwnerActorTag(ActorTag);
		}
	}
}

void UMemoryEventDefinition::SetDialogueContent(FGameplayTag ActorTag, const FDialogueContent& NewDialogueContent)
{
}

void UMemoryEventDefinition::GrantNewAbilities(FGameplayTagContainer AbilityTags)
{
	if (!GetGlobalAbilitySystem())return;

	GlobalAbilitySystem->GrantAbilitiesToAbilitySystem(AbilityTags);
}

void UMemoryEventDefinition::SwitchToInteractionCamera(FGameplayTag ActorTag)
{
	AActor* TargetActor = GetSceneActorByActorTag(ActorTag);
	if (PlayerController && TargetActor)
	{
		IPlayerControllerInterface::Execute_SwitchToInteractionCamera(PlayerController, TargetActor);
	}
}

void UMemoryEventDefinition::GenerateCharacterBehaviorCognition(const FGameplayTag& CharacterTag, const FName& ActionDesc)
{
	if (!PlayerController || !EventTag.IsValid())return;

	if (AMemoryPlayerState* MemoryPS = PlayerController->GetPlayerState<AMemoryPlayerState>())
	{
		MemoryPS->GenerateCharacterBehaviorCognition(CharacterTag, ActionDesc, EventTag);
	}
}

void UMemoryEventDefinition::GenerateSelfAwareness(const FGameplayTag& AwarenessTag, bool bInGroup, int32 Index)
{
	if (!PlayerController || !EventTag.IsValid())return;

	if (AMemoryPlayerState* MemoryPS = PlayerController->GetPlayerState<AMemoryPlayerState>())
	{
		MemoryPS->GenerateSelfAwareness(AwarenessTag, EventTag, bInGroup, Index);
	}
}

UMemoryGlobalAbilitySystem* UMemoryEventDefinition::GetGlobalAbilitySystem()
{
	check(WorldContext);

	if (!GlobalAbilitySystem)
	{
		GlobalAbilitySystem = WorldContext->GetSubsystem<UMemoryGlobalAbilitySystem>();
	}

	return GlobalAbilitySystem;
}

USpawnPointSubsystem* UMemoryEventDefinition::GetSpawnPointSubsystem()
{
	check(WorldContext);

	if (!SpawnPointSubsystem)
	{
		SpawnPointSubsystem = WorldContext->GetSubsystem<USpawnPointSubsystem>();
	}

	return SpawnPointSubsystem;
}