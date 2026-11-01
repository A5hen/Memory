// Fill out your copyright notice in the Description page of Project Settings.


#include "SelfAwarenessSet.h"

const FAwarenessInfo* USelfAwarenessSet::GetAwarenessInfo_Single(const FGameplayTag& AwarenessTag) const
{
	return AwarenessInfomation_Single.Find(AwarenessTag);
}

const FGameplayTagContainer* USelfAwarenessSet::GetSelfAwarenessGroup(FName GroupName) const
{
	return SelfAwarenessGroup.Find(GroupName);
}

const FAwarenessInfo* USelfAwarenessSet::GetAwarenessInfo_Group(FName GroupName) const
{
	return AwarenessInfomation_Group.Find(GroupName);
}