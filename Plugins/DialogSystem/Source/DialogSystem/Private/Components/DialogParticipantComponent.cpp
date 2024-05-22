// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/DialogParticipantComponent.h"

// Sets default values for this component's properties
UDialogParticipantComponent::UDialogParticipantComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDialogParticipantComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UDialogParticipantComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

UDataTable* UDialogParticipantComponent::GetDialogTable() const
{
	return DialogTable;
}

void UDialogParticipantComponent::JoinToDialog(UDialogManager* DialogManager)
{
	if (!DialogManager)
	{
		return;
	}

	if (DialogManager->SyncDialog(DialogTable))
	{
		DialogManager->StartDialog.Broadcast();
		DialogManager->BeginConversation();
	}
}

