// Fill out your copyright notice in the Description page of Project Settings.


#include "MemoryCharacter.h"
#include "AbilitySystemComponent.h"//
#include "GameFramework/CharacterMovementComponent.h"//
#include "GameFrameWork/SpringArmComponent.h"//
#include "Camera/CameraComponent.h"//

#include "Memory/Player/MemoryPlayerController.h"//
#include "Memory/Player/MemoryPlayerState.h"//
#include "Memory/HUD/MemoryHUD.h"//
#include "Memory/AbilitySystem/Ability/MemoryGameplayAbility.h"//
#include "Memory/GameMode/MemoryEventManager.h"//

AMemoryCharacter::AMemoryCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->bUsePawnControlRotation = true;
	SpringArmComponent->bDoCollisionTest = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera");
	CameraComponent->SetupAttachment(SpringArmComponent);

	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
}

UAbilitySystemComponent* AMemoryCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AMemoryCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ShouldHideCharacter();
}

void AMemoryCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	InitializeCharacter();
}

void AMemoryCharacter::InitializeCharacter()
{
	AMemoryPlayerState* MemoryPS = GetPlayerStateChecked<AMemoryPlayerState>();

	AbilitySystemComponent = MemoryPS->GetAbilitySystemComponent();
	AbilitySystemComponent->InitAbilityActorInfo(MemoryPS, this);

	MemoryPS->SetPawnData();

	if (AMemoryPlayerController* MemoryPC = Cast<AMemoryPlayerController>(GetController()))
	{
		if (AMemoryHUD* MemoryHUD = Cast<AMemoryHUD>(MemoryPC->GetHUD()))
		{
			MemoryHUD->InitRootLayout();
			MemoryHUD->InitOverlay(MemoryPC, MemoryPS, AbilitySystemComponent, AttributeSet);
		}

		if (UMemoryEventManager* EventManager = GetWorld()->GetSubsystem<UMemoryEventManager>())
		{
			EventManager->SetPlayerController(MemoryPC);
			EventManager->ConfirmStartEventCondition("Player");
		}
	}
}

void AMemoryCharacter::ShouldHideCharacter()
{
	if ((CameraComponent->GetComponentLocation() - GetActorLocation()).Size() < CameraThreshold)
	{
		GetMesh()->SetVisibility(false);
	}
	else
	{
		GetMesh()->SetVisibility(true);
	}
}