// Fill out your copyright notice in the Description page of Project Settings.


#include "MemoryGameplayTag.h"
#include "GameplayTagsManager.h"

FMemoryGameplayTags FMemoryGameplayTags::GameplayTags;

void FMemoryGameplayTags::InitializeNativeGameplayTags()
{
    /*Ability*/
    GameplayTags.Ability_Interact = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("Ability.Interact"),
        FString("Interact Ability"));

    GameplayTags.Ability_Extra_Up = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("Ability.Extra.Up"),
        FString("Increase the option index"));

    GameplayTags.Ability_Extra_Down = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("Ability.Extra.Down"),
        FString("Decrease the option index"));

    GameplayTags.State_Interacting = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("State.Interacting"),
        FString("Interacting"));
    /*Ability*/

    /*Layer*/
    GameplayTags.Layer_GameAndMenu = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("Layer.GameAndMenu"),
        FString("GameAndMenuLayer"));

    GameplayTags.Layer_Game = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("Layer.Game"),
        FString("GameLayer"));

    GameplayTags.Layer_Menu = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("Layer.Menu"),
        FString("MenuLayer"));

    GameplayTags.Layer_Dialogue = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("Layer.Dialogue"),
        FString("DialogueLayer"));

    GameplayTags.Layer_Selection = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("Layer.Selection"),
        FString("SelectionLayer"));
    /*Layer*/

    /*Widget*/
    GameplayTags.Widget_MainMenu = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("Widget.MainMenu"),
        FString("MainMenu"));

    GameplayTags.Widget_EventMenu = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("Widget.EventMenu"),
        FString("EventMenu"));

    GameplayTags.Widget_CharacterCognitionMenu = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("Widget.CharacterCognitionMenu"),
        FString("CharacterCognitionMenu"));

    GameplayTags.Widget_SelfAwarenessMenu = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("Widget.SelfAwarenessMenu"),
        FString("SelfAwarenessMenu"));
    /*Widget*/

    /*Content*/
    GameplayTags.Content_Event = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("Content.Event"),
        FString("Event"));

    GameplayTags.Content_Character = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("Content.Character"),
        FString("Character"));

    GameplayTags.Content_CharacterBehavior = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("Content.CharacterBehavior"),
        FString("CharacterBehavior"));

    GameplayTags.Content_BehaviorCognition = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("Content.BehaviorCognition"),
        FString("BehaviorCognition"));

    GameplayTags.Content_SelfAwareness = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("Content.SelfAwareness"),
        FString("SelfAwareness"));

    GameplayTags.Content_Ability = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("Content.Ability"),
        FString("Ability"));

    GameplayTags.Content_AttributeEffect = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("Content.AttributeEffect"),
        FString("AttributeEffect"));
    /*Content*/

    /*ActorTag*/
    GameplayTags.Character_Grandfather = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("Character.Grandfather"),
        FString("Grandfather"));

    GameplayTags.Character_Grandmother = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("Character.Grandmother"),
        FString("Grandmother"));

    GameplayTags.Character_Father = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("Character.Father"),
        FString("Mother"));

    GameplayTags.Character_Mother = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("Character.Mother"),
        FString("Mother"));
    /*ActorTag*/

    //Test
    GameplayTags.Event_Test = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("Event.Test"),
        FString("TestEvent"));

    GameplayTags.Event_Test2 = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("Event.Test2"),
        FString("TestEvent2"));

    GameplayTags.SpawnPoint_Test = UGameplayTagsManager::Get().AddNativeGameplayTag(
        FName("SpawnPoint.Test"),
        FString("TestSpawnPoint"));
}