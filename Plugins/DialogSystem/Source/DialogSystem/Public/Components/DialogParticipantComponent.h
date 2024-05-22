// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DialogManager.h"
#include "Components/ActorComponent.h"
#include "DialogParticipantComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FStartDialog);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DIALOGSYSTEM_API UDialogParticipantComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDialogParticipantComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (RequiredAssetDataTags = "RowStructure=/Script/DialogSystem.SentenceRow"))
	UDataTable* DialogTable;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UDataTable* GetDialogTable() const;

	// Event triggered whenever this object is used in any way (either Primary or Secondary).
	UFUNCTION(BlueprintCallable)
	void JoinToDialog(UDialogManager* DialogManager);

	// Event triggered whenever this object is used in any way (either Primary or Secondary).
	UPROPERTY(BlueprintAssignable, Meta = (DisplayName = "On Prepare For Dialog"), Category = "Events")
	FStartDialog OnPrepareForDialog;

	// Event triggered whenever this object is used in any way (either Primary or Secondary).
	UPROPERTY(BlueprintAssignable, Meta = (DisplayName = "On Canceled Prepare For Dialog"), Category = "Events")
	FStartDialog OnCanceledPrepareForDialog;
};
