// Fill out your copyright notice in the Description page of Project Settings.


#include "MemoryPlayerController.h"
#include "EnhancedInputSubsystems.h"//
#include "AbilitySystemBlueprintLibrary.h"//
#include "Memory/Input/MemoryInputComponent.h"//
#include "Memory/HUD/MemoryHUD.h"//
#include "Memory/AbilitySystem/MemoryAbilitySystemComponent.h"//
#include "Memory/MemoryGameplayTag.h"//

void AMemoryPlayerController::PreProcessInput(const float DeltaTime, const bool bGamePaused)
{
    Super::PreProcessInput(DeltaTime, bGamePaused);
}

void AMemoryPlayerController::PostProcessInput(const float DeltaTime, const bool bGamePaused)
{
    if (GetMemoryASC())
    {
        MemoryASC->ProcessAbilityInput(DeltaTime, bGamePaused);
    }

    Super::PostProcessInput(DeltaTime, bGamePaused);
}

void AMemoryPlayerController::SwitchToInteractionCamera_Implementation(AActor* TargetActor)
{
    if(TargetActor)
    {
        SetViewTargetWithBlend(TargetActor, 0.35, EViewTargetBlendFunction::VTBlend_Cubic);
    }
}

void AMemoryPlayerController::RestoreCamera_Implementation()
{
	if (APawn* ControlledPawn = GetPawn())
    {
        SetViewTargetWithBlend(ControlledPawn, 0.25, EViewTargetBlendFunction::VTBlend_Cubic);
    }
}

void AMemoryPlayerController::BeginPlay()
{
    Super::BeginPlay();

    UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
    if (Subsystem)
    {
        Subsystem->AddMappingContext(InputMappingContext, 0);
    }

     FInputModeGameOnly InputModeData;
     SetInputMode(InputModeData);
}

void AMemoryPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

    UMemoryInputComponent* MemoryInputComponent = CastChecked<UMemoryInputComponent>(InputComponent);

    MemoryInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMemoryPlayerController::Move);
    MemoryInputComponent->BindAction(CameraMoveAction, ETriggerEvent::Triggered, this, &AMemoryPlayerController::CameraMove);
    MemoryInputComponent->BindAction(OpenMainMenuAction, ETriggerEvent::Started, this, &AMemoryPlayerController::OpenMainMenu);

    MemoryInputComponent->BindAbilityActions(InputConfig, this,
        &AMemoryPlayerController::AbilityInputTagPressed,
        &AMemoryPlayerController::AbilityInputTagReleased);
}

void AMemoryPlayerController::Move(const FInputActionValue& InputActionValue)
{
    const FMemoryGameplayTags& GameplayTag = FMemoryGameplayTags::Get();
    if (GetMemoryASC())
    {
        if (MemoryASC->HasMatchingGameplayTag(GameplayTag.State_Interacting))return;
    }

    const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();

    const FRotator YawRotation = FRotator(0.f, GetControlRotation().Yaw, 0.f);

    const FVector ForwardVector = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
    const FVector RightVector = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

    if (APawn* ControlledPawn = GetPawn<APawn>())
    {
        ControlledPawn->AddMovementInput(ForwardVector, InputAxisVector.Y);
        ControlledPawn->AddMovementInput(RightVector, InputAxisVector.X);
    }
}

void AMemoryPlayerController::CameraMove(const FInputActionValue& InputActionValue)
{
    const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();

    if (APawn* ControlledPawn = GetPawn<APawn>())
    {
        ControlledPawn->AddControllerYawInput(InputAxisVector.X);
        ControlledPawn->AddControllerPitchInput(-InputAxisVector.Y);
    }
}

void AMemoryPlayerController::OpenMainMenu(const FInputActionValue& InputActionValue)
{
    const FMemoryGameplayTags& GameplayTag = FMemoryGameplayTags::Get();

    if (GetMemoryASC())
    {
        if (MemoryASC->HasMatchingGameplayTag(GameplayTag.State_Interacting))return;
    }

    if (AMemoryHUD* MemoryHUD = Cast<AMemoryHUD>(GetHUD()))
    {
        MemoryHUD->PushMainMenu();
    }
}

void AMemoryPlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{
    if (GetMemoryASC())
    {
        MemoryASC->AbilityInputTagPressed(InputTag);
    }
}

void AMemoryPlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
    if (GetMemoryASC())
    {
        MemoryASC->AbilityInputTagReleased(InputTag);
    }
}

UMemoryAbilitySystemComponent* AMemoryPlayerController::GetMemoryASC()
{
    if (MemoryASC == nullptr)
    {
        MemoryASC = Cast<UMemoryAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn<APawn>()));
    }
    return MemoryASC;
}