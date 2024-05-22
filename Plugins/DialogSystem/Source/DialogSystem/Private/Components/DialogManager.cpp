// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/DialogManager.h"

#include "Blueprint/UserWidget.h"

// Sets default values for this component's properties
UDialogManager::UDialogManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UDialogManager::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


FText UDialogManager::CreateSentence(FSentenceRow* SentenceRow)
{
	FString Result = SentenceRow->SpeakerName.ToString() + ": " + SentenceRow->SentenceText.ToString();
	return FText::FromString(Result);
}

void UDialogManager::ProcessDialogRow(FName SentenceName)
{
	CurrentSentence = DialogTable->FindRow<FSentenceRow>(SentenceName, "");

	if (!CurrentSentence)
	{
		EndConversation();
		EndDialog.Broadcast();
		return;
	}

	if (CurrentSentence->SentenceType == ESentenceType::Default)
	{
		FText SentenceText = CreateSentence(CurrentSentence);

		OnSentenceUpdated.Broadcast(SentenceText);
	}
	else
	{
		OnResponseUpdated.Broadcast(CurrentSentence->Responses);
	}
}

bool UDialogManager::SyncDialog(UDataTable* ParticipantDialogTable)
{
	if (!ParticipantDialogTable)
	{
		return false;
	}

	DialogTable = ParticipantDialogTable;
	return true;
}

void UDialogManager::TryProcessNextDialogRow()
{
	if (CurrentSentence->LastSentence)
	{
		EndConversation();
		EndDialog.Broadcast();
		return;
	}

	ProcessDialogRow(CurrentSentence->NextSentenceName);
}

void UDialogManager::TryProcessNextDialogRowAfterResponse(FName SentenceRowName)
{
	if (CurrentSentence->LastSentence)
	{
		EndConversation();
		EndDialog.Broadcast();
		return;
	}

	ProcessDialogRow(SentenceRowName);
}

// Called every frame
void UDialogManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UDialogManager::BeginConversation()
{
	ProcessDialogRow(StartSentence);
	PrimaryComponentTick.bCanEverTick = true;
}

void UDialogManager::EndConversation()
{
	PrimaryComponentTick.bCanEverTick = false;
}

