// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameplayTagContainer.h"//
#include "Memory/Player/PlayerControllerInterface.h"//
#include "MemoryPlayerController.generated.h"

struct FInputActionValue;
class UInputAction;
class UInputMappingContext;

class UMemoryInputConfig;

class UMemoryAbilitySystemComponent;

/**
 * 
 */
UCLASS()
class MEMORY_API AMemoryPlayerController : public APlayerController ,public IPlayerControllerInterface
{
	GENERATED_BODY()

public:

	virtual void PreProcessInput(const float DeltaTime, const bool bGamePaused) override;
	virtual void PostProcessInput(const float DeltaTime, const bool bGamePaused) override;

	/*~PlayerController Interface*/
	void SwitchToInteractionCamera_Implementation(AActor* TargetActor);
	void RestoreCamera_Implementation();
	/*~End of PlayerController Interface*/

protected:

	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:

	void Move(const FInputActionValue& InputActionValue);
	void CameraMove(const FInputActionValue& InputActionValue);
	void OpenMainMenu(const FInputActionValue& InputActionValue);

	void AbilityInputTagPressed(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);

	UMemoryAbilitySystemComponent* GetMemoryASC();

private:

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext>InputMappingContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction>MoveAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction>CameraMoveAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction>OpenMainMenuAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UMemoryInputConfig> InputConfig;

	UPROPERTY()
	TObjectPtr<UMemoryAbilitySystemComponent> MemoryASC;
};