// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC/BaseNPC.h"
#include "Components/CapsuleComponent.h"
#include "Components/DialogParticipantComponent.h"

// Sets default values
ABaseNPC::ABaseNPC()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	DialogParticipantComponent = CreateDefaultSubobject<UDialogParticipantComponent>(TEXT("DialogParticipant"));
	AddOwnedComponent(DialogParticipantComponent);
}

// Called when the game starts or when spawned
void ABaseNPC::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseNPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABaseNPC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

