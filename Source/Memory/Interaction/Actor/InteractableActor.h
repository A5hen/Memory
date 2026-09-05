// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Memory/Interaction/InteractableTarget.h"//
#include "Memory/Interaction/InteractionOption.h"//
#include "InteractableActor.generated.h"

class UWidgetComponent;
class USphereComponent;

class UOptionWidget;

UCLASS()
class MEMORY_API AInteractableActor : public AActor, public IInteractableTarget
{
	GENERATED_BODY()
	
public:	

	AInteractableActor();
	virtual void Tick(float DeltaTime) override;

	/*~InteractableTarget Interface*/
	virtual void GatherInteractionOptions(const FInteractionQuery& InteractQuery, FInteractionOptionBuilder& OptionBuilder)override;
	virtual bool IsInteractable()const override;
	/*~End of InteractableTarget Interface*/

protected:

	virtual void BeginPlay() override;
	virtual void Destroyed() override;

	void FacingPlayer();

protected:

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> RootSphere;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UWidgetComponent> WidgetContainer;

	UPROPERTY(EditDefaultsOnly, Category = "InteractableActor|Option")
	TArray<FInteractionOption> InteractionOptions;

	UPROPERTY(EditDefaultsOnly, Category = "InteractableActor|Option")
	TSubclassOf<UOptionWidget> OptionWidgetClass;

	FTimerHandle TimerHandle;

	bool bShowOption = false;
};