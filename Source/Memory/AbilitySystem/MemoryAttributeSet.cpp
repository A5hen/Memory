// Fill out your copyright notice in the Description page of Project Settings.


#include "MemoryAttributeSet.h"

UMemoryAttributeSet::UMemoryAttributeSet()
{
}

void UMemoryAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeBaseChange(Attribute, NewValue);
}

void UMemoryAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	Super::PostAttributeBaseChange(Attribute, OldValue, NewValue);
}

void UMemoryAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
}