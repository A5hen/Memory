// Fill out your copyright notice in the Description page of Project Settings.


#include "SelfAwarenessSet.h"

const FAwarenessInfo* USelfAwarenessSet::GetAwarenessInfo_Single(const FGameplayTag& AwarenessTag) const
{
	return AwarenessInfomation_Single.Find(AwarenessTag);
}

const FGameplayTagContainer* USelfAwarenessSet::GetTagContainerKey(int32 Index) const
{
	return IndexToTagContainerKey.Find(Index);
}

const FAwarenessInfo* USelfAwarenessSet::GetAwarenessInfo_Group(int32 Index) const
{
	return AwarenessInfomation_Group.Find(Index);
}