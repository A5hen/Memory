// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"//
#include "MemoryCharacter.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;
class UGameplayAbility;

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class MEMORY_API AMemoryCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:

	AMemoryCharacter();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const { return AttributeSet; };

	virtual void Tick(float DeltaTime) override;
	virtual void PossessedBy(AController* NewController)override;

protected:

	void InitializeCharacter();

	void ShouldHideCharacter();

	UPROPERTY(VisibleAnywhere, Category = "Camera")
	TObjectPtr<USpringArmComponent> SpringArmComponent;

	UPROPERTY(VisibleAnywhere, Category = "Camera")
	TObjectPtr<UCameraComponent> CameraComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Camera")
	float CameraThreshold = 200.f;

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;
};