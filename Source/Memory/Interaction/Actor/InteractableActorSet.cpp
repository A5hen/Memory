// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableActorSet.h"

const FInteractableActorInfo* UInteractableActorSet::GetInteractableActorInfo(int32 ActorID) const
{
	return InteractableActorInfomation.Find(ActorID);
}