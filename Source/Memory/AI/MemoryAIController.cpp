// Fill out your copyright notice in the Description page of Project Settings.


#include "MemoryAIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"//
#include "BehaviorTree/BlackboardComponent.h"

AMemoryAIController::AMemoryAIController()
{
	Blackboard = CreateDefaultSubobject<UBlackboardComponent>("Balckboard");
	check(Blackboard);
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>("BehaviorTree");
	check(BehaviorTreeComponent);
}