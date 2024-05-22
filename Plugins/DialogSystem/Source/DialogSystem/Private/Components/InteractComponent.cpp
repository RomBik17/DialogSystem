// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/InteractComponent.h"
#include "Components/DialogParticipantComponent.h"


// Sets default values for this component's properties
UInteractComponent::UInteractComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInteractComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UInteractComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UInteractComponent::ClearCache()
{
	if (bCanInteract && CashedDialogParticipantComponent)
	{
		CashedDialogParticipantComponent->OnCanceledPrepareForDialog.Broadcast();
	}

	bCanInteract = false;
	CashedDialogParticipantComponent = nullptr;
}

void UInteractComponent::UpdateCache(UDialogParticipantComponent* InCashe)
{
	CashedDialogParticipantComponent = InCashe;
	bCanInteract = true;

	if (bCanInteract && CashedDialogParticipantComponent)
	{
		CashedDialogParticipantComponent->OnPrepareForDialog.Broadcast();
	}
}

bool UInteractComponent::TryToInteract(UDialogManager* DialogManager)
{
	if (!DialogManager)
	{
		return false;
	}

	if (bCanInteract && CashedDialogParticipantComponent)
	{
		CashedDialogParticipantComponent->JoinToDialog(DialogManager);
		return true;
	}

	return false;
}

float UInteractComponent::GetInteractDistance() const
{
	return InteractDistance;
}

void UInteractComponent::ScanForDialogPersonInView(FCollisionQueryParams& QueryParams)
{
	APlayerCameraManager* CameraManager = GetWorld()->GetFirstPlayerController()->PlayerCameraManager;
	FVector TraceStart = CameraManager->GetCameraLocation();
	FVector TraceEnd = TraceStart + CameraManager->GetCameraRotation().Vector() * InteractDistance;

	FHitResult Hit;

	GetWorld()->LineTraceSingleByChannel(Hit, TraceStart, TraceEnd, ECC_Visibility, QueryParams);

	if (Hit.bBlockingHit && IsValid(Hit.GetActor()))
	{
		if (UDialogParticipantComponent* PrepCache = Hit.GetActor()->FindComponentByClass<UDialogParticipantComponent>())
		{
			UpdateCache(PrepCache);
		}
	}
	else
	{
		ClearCache();
	}
}