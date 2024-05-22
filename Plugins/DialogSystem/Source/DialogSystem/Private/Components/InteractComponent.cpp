// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/InteractComponent.h"
#include "Components/UsableComponent.h"

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
	if (bCanInteract && CashedUsableComponent)
	{
		CashedUsableComponent->OnCanceledPrepareForUsing.Broadcast();
	}

	bCanInteract = false;
	CashedUsableComponent = nullptr;
}

void UInteractComponent::UpdateCache(UUsableComponent* InCashe)
{
	CashedUsableComponent = InCashe;
	bCanInteract = true;

	if (bCanInteract && CashedUsableComponent)
	{
		CashedUsableComponent->OnPrepareForUsing.Broadcast();
	}
}

void UInteractComponent::TryToInteract()
{
	if (bCanInteract && CashedUsableComponent)
	{
		CashedUsableComponent->OnUsed.Broadcast();
	}
}

float UInteractComponent::GetInteractDistance() const
{
	return InteractDistance;
}

void UInteractComponent::ScanForUsableObjectInView(FCollisionQueryParams& QueryParams)
{
	APlayerCameraManager* CameraManager = GetWorld()->GetFirstPlayerController()->PlayerCameraManager;
	FVector TraceStart = CameraManager->GetCameraLocation();
	FVector TraceEnd = TraceStart + CameraManager->GetCameraRotation().Vector() * InteractDistance;

	FHitResult Hit;

	GetWorld()->LineTraceSingleByChannel(Hit, TraceStart, TraceEnd, ECC_Visibility, QueryParams);

	if (Hit.bBlockingHit && IsValid(Hit.GetActor()))
	{
		if (UUsableComponent* PrepCache = Hit.GetActor()->FindComponentByClass<UUsableComponent>())
		{
			UpdateCache(PrepCache);
		}
	}
	else
	{
		ClearCache();
	}
}