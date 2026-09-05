// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Memory/Interaction/InteractableTarget.h"//
#include "Memory/Interaction/InteractionOption.h"//
#include "InteractableCharacter.generated.h"

class UWidgetComponent;
class USphereComponent;
class UCameraComponent;

class UOptionWidget;

class UBehaviorTree;
class AMemoryAIController;

UCLASS()
class MEMORY_API AInteractableCharacter : public ACharacter, public IInteractableTarget
{
	GENERATED_BODY()
	
public:	

	AInteractableCharacter();

	virtual void Tick(float DeltaTime) override;
	virtual void PossessedBy(AController* NewController) override;

	/*~InteractableTarget Interface*/
	virtual void GatherInteractionOptions(const FInteractionQuery& InteractQuery, FInteractionOptionBuilder& OptionBuilder) override;
	virtual void DisplayOption(const FName& ID, bool bDisplay) override;
	virtual void SelectOption(const FName& ID, bool bSelect) override;
	virtual bool IsInteractable() const override;

	virtual FGameplayTag GetActorTag()const override;

	virtual void GetDialogueContent(FDialogueContent& OutDialogueContent) const override;
	virtual void SetDialogueContent(const FDialogueContent& NewDialogueContent) override;

	virtual void CharacterMove(AActor* TargetPoint)override;
	/*~End of InteractableTarget Interface*/

protected:

	virtual void BeginPlay() override;
	virtual void Destroyed() override;

	UFUNCTION()
	void OnInteractionSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnInteractionSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void FacingPlayer();

protected:
	
	UPROPERTY(EditAnywhere, Category = "InteractableCharacter")
	FGameplayTag CharacterTag;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> RootSphere;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UWidgetComponent> WidgetContainer;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> InteractionSphere;

	UPROPERTY(EditDefaultsOnly, Category = "InteractableCharacter|Option")
	TArray<FInteractionOption> InteractionOptions;

	UPROPERTY(EditDefaultsOnly, Category = "InteractableCharacter|Option")
	TSubclassOf<UOptionWidget> OptionWidgetClass;

	UPROPERTY(VisibleAnywhere, Category = "Camera")
	TObjectPtr<UCameraComponent> InteractionCamera;

	FTimerHandle TimerHandle;

	bool bTimerSet = false;

	bool bInteractable = true;

	/*AI*/
	UPROPERTY(EditAnywhere, Category = "InteractableCharacter|AI")
	TObjectPtr<UBehaviorTree> BehaviorTree;

	UPROPERTY()
	TObjectPtr<AMemoryAIController> AIController;
	/*AI*/

	/*Dialogue*/
	UPROPERTY(EditDefaultsOnly, Category = "InteractableCharacter|DialogueContent")
	FDialogueContent DialogueContent;

	UPROPERTY(EditDefaultsOnly, Category = "InteractableCharacter|DialogueContent")
	int32 DialogueBranchIndex = 0;
	/*Dialogue*/
};