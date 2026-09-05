// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableCharacter.h"
#include "Components/WidgetComponent.h"//
#include "Components/SphereComponent.h"//
#include "Camera/CameraComponent.h"//
#include "BehaviorTree/BehaviorTree.h"//
#include "BehaviorTree/BlackboardComponent.h"//
#include "Memory/UI/OptionWidgetContainer.h"//
#include "Memory/UI/OptionWidget.h"//
#include "Memory/AI/MemoryAIController.h"//

AInteractableCharacter::AInteractableCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	RootSphere = CreateDefaultSubobject<USphereComponent>("RootSphere");
	RootSphere->SetupAttachment(GetRootComponent());

	WidgetContainer = CreateDefaultSubobject<UWidgetComponent>("WidgetContainer");
	WidgetContainer->SetupAttachment(RootSphere);

	InteractionSphere = CreateDefaultSubobject<USphereComponent>("InteractionSphere");
	InteractionSphere->SetupAttachment(RootSphere);

	InteractionCamera = CreateDefaultSubobject<UCameraComponent>("InteractionCamera");
	InteractionCamera->SetupAttachment(RootSphere);

	WidgetContainer->SetWidgetSpace(EWidgetSpace::World);
	WidgetContainer->SetVisibility(false);
}

void AInteractableCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AInteractableCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (!BehaviorTree)return;

	AIController = Cast<AMemoryAIController>(NewController);
	if (AIController)
	{
		AIController->GetBlackboardComponent()->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
		AIController->RunBehaviorTree(BehaviorTree);
	}
}

void AInteractableCharacter::BeginPlay()
{
	Super::BeginPlay();

	InteractionSphere->OnComponentBeginOverlap.AddDynamic(this, &AInteractableCharacter::OnInteractionSphereBeginOverlap);
	InteractionSphere->OnComponentEndOverlap.AddDynamic(this, &AInteractableCharacter::OnInteractionSphereEndOverlap);

	UOptionWidgetContainer* OptionContainer = Cast<UOptionWidgetContainer>(WidgetContainer->GetUserWidgetObject());
	if (OptionContainer)
	{
		for (const FInteractionOption& InteractionOption : InteractionOptions)
		{
			UOptionWidget* OptionWidget = CreateWidget<UOptionWidget>(GetWorld(), OptionWidgetClass);
			OptionWidget->SetOptionText(InteractionOption.Option);

			OptionContainer->AddOptionWidget(InteractionOption.ID, OptionWidget);
		}
	}
}

void AInteractableCharacter::Destroyed()
{
	if (UWorld* World = GetWorld())
	{
		World->GetTimerManager().ClearTimer(TimerHandle);
	}

	Super::Destroyed();
}

void AInteractableCharacter::OnInteractionSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(ACharacter* Character = Cast<ACharacter>(OtherActor))
	{
		bInteractable = true;
	}
}

void AInteractableCharacter::OnInteractionSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (ACharacter* Character = Cast<ACharacter>(OtherActor))
	{
		bInteractable = false;
	}
}

void AInteractableCharacter::FacingPlayer()
{
	if (UWorld* World = GetWorld())
	{
		FRotator CameraRotation = World->GetFirstPlayerController()->PlayerCameraManager->GetCameraRotation();

		FRotator WidgetComponentRotator = FRotator(0.f, CameraRotation.Yaw + 180.f, 0.f);
		WidgetContainer->SetWorldRotation(WidgetComponentRotator);
	}
}

void AInteractableCharacter::GatherInteractionOptions(const FInteractionQuery& InteractQuery, FInteractionOptionBuilder& OptionBuilder)
{
	if (IsInteractable())
	{
		for (FInteractionOption& Option : InteractionOptions)
		{
			OptionBuilder.AddInteractionOption(Option);
		}
	}
}

void AInteractableCharacter::DisplayOption(const FName& ID, bool bDisplay)
{
	UOptionWidgetContainer* OptionContainer = Cast<UOptionWidgetContainer>(WidgetContainer->GetUserWidgetObject());
	OptionContainer->DisplayOptionWidget(ID, bDisplay);

	if (UWorld* World = GetWorld())
	{
		if (OptionContainer->IsAnyOptionDisplayed())
		{
			if (WidgetContainer->IsVisible() == false)
			{
				WidgetContainer->SetVisibility(true);
			}

			if (!bTimerSet)
			{
				World->GetTimerManager().SetTimer(TimerHandle, this, &AInteractableCharacter::FacingPlayer, 0.01f, true, 0.f);
				bTimerSet = true;
			}
		}
		else
		{
			if (WidgetContainer->IsVisible() != false)
			{
				WidgetContainer->SetVisibility(false);
			}

			if (bTimerSet)
			{
				World->GetTimerManager().ClearTimer(TimerHandle);
			}
		}
	}
}

void AInteractableCharacter::SelectOption(const FName& ID, bool bSelect)
{
}

bool AInteractableCharacter::IsInteractable() const
{
	return bInteractable;
}

FGameplayTag AInteractableCharacter::GetActorTag() const
{
	return CharacterTag;
}

void AInteractableCharacter::GetDialogueContent(FDialogueContent& OutDialogueContent) const
{
	OutDialogueContent = DialogueContent;
}

void AInteractableCharacter::SetDialogueContent(const FDialogueContent& NewDialogueContent)
{
	DialogueContent = NewDialogueContent;
}

void AInteractableCharacter::CharacterMove(AActor* TargetPoint)
{
	if (AIController && TargetPoint)
	{
		AIController->GetBlackboardComponent()->SetValueAsObject(FName("TargetPoint"), TargetPoint);
	}
}