// Fill out your copyright notice in the Description page of Project Settings.


#include "MemoryEventSet.h"

const FMemoryEventInfo* UMemoryEventSet::GetEventInfoByEventTag(const FGameplayTag& EventTag) const
{
	return EventInfomation.Find(EventTag);
}

void UMemoryEventSet::GenerateEventConnectInfo(EPreEventConnectType PreEventConnectType, const FVector2D& Start, const FVector2D& End, float InstigatorSize, float TargetSize, FVector2D& OutStart, FVector2D& OutEnd)
{
	switch (PreEventConnectType)
	{
	case EPreEventConnectType::TopToBottom:
		OutStart = FVector2D(Start.X, Start.Y - InstigatorSize);
		OutEnd = FVector2D(End.X, End.Y + TargetSize);
		break;
	case EPreEventConnectType::TopToLeft:
		OutStart = FVector2D(Start.X, Start.Y - InstigatorSize);
		OutEnd = FVector2D(End.X - TargetSize, End.Y);
		break;
	case EPreEventConnectType::TopToRight:
		OutStart = FVector2D(Start.X, Start.Y - InstigatorSize);
		OutEnd = FVector2D(End.X + TargetSize, End.Y);
		break;

	case EPreEventConnectType::BottomToTop:
		OutStart = FVector2D(Start.X, Start.Y + InstigatorSize);
		OutEnd = FVector2D(End.X, End.Y - TargetSize);
		break;
	case EPreEventConnectType::BottomToLeft:
		OutStart = FVector2D(Start.X, Start.Y + InstigatorSize);
		OutEnd = FVector2D(End.X - TargetSize, End.Y);
		break;
	case EPreEventConnectType::BottomToRight:
		OutStart = FVector2D(Start.X, Start.Y + InstigatorSize);
		OutEnd = FVector2D(End.X + TargetSize, End.Y);
		break;

	case EPreEventConnectType::LeftToTop:
		OutStart = FVector2D(Start.X - InstigatorSize, Start.Y);
		OutEnd = FVector2D(End.X, End.Y - TargetSize);
		break;
	case EPreEventConnectType::LeftToBottom:
		OutStart = FVector2D(Start.X - InstigatorSize, Start.Y);
		OutEnd = FVector2D(End.X, End.Y + TargetSize);
		break;
	case EPreEventConnectType::LeftToRight:
		OutStart = FVector2D(Start.X - InstigatorSize, Start.Y);
		OutEnd = FVector2D(End.X + TargetSize, End.Y);
		break;

	case EPreEventConnectType::RightToTop:
		OutStart = FVector2D(Start.X + InstigatorSize, Start.Y);
		OutEnd = FVector2D(End.X, End.Y - TargetSize);
		break;
	case EPreEventConnectType::RightToBottom:
		OutStart = FVector2D(Start.X + InstigatorSize, Start.Y);
		OutEnd = FVector2D(End.X, End.Y + TargetSize);
		break;
	case EPreEventConnectType::RightToLeft:
		OutStart = FVector2D(Start.X + InstigatorSize, Start.Y);
		OutEnd = FVector2D(End.X - TargetSize, End.Y);
		break;
	}
}