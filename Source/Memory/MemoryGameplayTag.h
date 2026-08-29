// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"//

/**
 * 
 */

struct FMemoryGameplayTags
{

public:

	static const FMemoryGameplayTags& Get() { return GameplayTags; }

	static void InitializeNativeGameplayTags();

public:

	FGameplayTag Ability_Interact;
	FGameplayTag Ability_Extra_Up;
	FGameplayTag Ability_Extra_Down;

	FGameplayTag State_Interacting;

	FGameplayTag Layer_GameAndMenu;
	FGameplayTag Layer_Game;
	FGameplayTag Layer_Menu;
	FGameplayTag Layer_Dialogue;
	FGameplayTag Layer_Selection;

	FGameplayTag Widget_MainMenu;
	FGameplayTag Widget_EventMenu;
	FGameplayTag Widget_CharacterCognitionMenu;
	FGameplayTag Widget_SelfAwarenessMenu;
	
	FGameplayTag Content_Event;
	FGameplayTag Content_Character;
	FGameplayTag Content_CharacterBehavior;
	FGameplayTag Content_BehaviorCognition;
	FGameplayTag Content_SelfAwareness;
	FGameplayTag Content_Ability;
	FGameplayTag Content_AttributeEffect;

	FGameplayTag Character_Grandfather;
	FGameplayTag Character_Grandmother;
	FGameplayTag Character_Father;
	FGameplayTag Character_Mother;

	FGameplayTag Event_Test;
	FGameplayTag Event_Test2;

	FGameplayTag SpawnPoint_Test;

private:

	static FMemoryGameplayTags GameplayTags;
};