// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableActor.h"
#include "Components/WidgetComponent.h"//
#include "Components/SphereComponent.h"//
#include "Memory/UI/OptionWidgetContainer.h"//
#include "Memory/UI/OptionWidget.h"//

AInteractableActor::AInteractableActor()
{
	PrimaryActorTick.bCanEverTick = false;

	RootSphere = CreateDefaultSubobject<USphereComponent>("RootSphere");
	RootSphere->SetupAttachment(GetRootComponent());

	WidgetContainer = CreateDefaultSubobject<UWidgetComponent>("WidgetContainer");
	WidgetContainer->SetupAttachment(RootSphere);

	WidgetContainer->SetWidgetSpace(EWidgetSpace::World);
	WidgetContainer->SetVisibility(false);
}

void AInteractableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AInteractableActor::GatherInteractionOptions(const FInteractionQuery& InteractQuery, FInteractionOptionBuilder& OptionBuilder)
{
	if (IsInteractable())
	{
		for (FInteractionOption& Option : InteractionOptions)
		{
			OptionBuilder.AddInteractionOption(Option);
		}
	}
}

void AInteractableActor::ShowOption(const FInteractionOption& Option, bool bShow)
{
	if (bShow == bShowOption)return;

	bShowOption = bShow;

	WidgetContainer->SetVisibility(bShow);

	if (UWorld* World = GetWorld())
	{
		if (bShow)
		{
			World->GetTimerManager().SetTimer(TimerHandle, this, &AInteractableActor::FacingPlayer, 0.01f, true, 0.f);
		}
		else
		{
			World->GetTimerManager().ClearTimer(TimerHandle);
		}
	}
}

void AInteractableActor::SelectOption(const FInteractionOption& Option, bool bSelect)
{
}

bool AInteractableActor::IsInteractable() const
{
	return true;
}

void AInteractableActor::BeginPlay()
{
	Super::BeginPlay();
	
	UOptionWidgetContainer* OptionContainer = Cast<UOptionWidgetContainer>(WidgetContainer->GetUserWidgetObject());
	if (OptionContainer)
	{
		for (const FInteractionOption& InteractionOption : InteractionOptions)
		{
			UOptionWidget* OptionWidget = CreateWidget<UOptionWidget>(GetWorld(), OptionWidgetClass);
			OptionWidget->SetOptionInfo(InteractionOption.Option);

			OptionContainer->AddOptionWidget(OptionWidget);
		}
	}
}

void AInteractableActor::Destroyed()
{
	if (UWorld* World = GetWorld())
	{
		World->GetTimerManager().ClearTimer(TimerHandle);
	}

	Super::Destroyed();
}

void AInteractableActor::FacingPlayer()
{
	if (UWorld* World = GetWorld())
	{
		FRotator CameraRotation = World->GetFirstPlayerController()->PlayerCameraManager->GetCameraRotation();

		FRotator WidgetComponentRotator = FRotator(0.f, CameraRotation.Yaw + 180.f, 0.f);
		WidgetContainer->SetWorldRotation(WidgetComponentRotator);
	}
}