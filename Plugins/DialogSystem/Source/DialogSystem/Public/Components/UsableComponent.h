// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UsableComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FUsableUsedSignature);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DIALOGSYSTEM_API UUsableComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UUsableComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	// Event triggered whenever this object is used in any way (either Primary or Secondary).
	UPROPERTY(BlueprintAssignable, Meta = (DisplayName = "On Used Any"), Category = "Events")
	FUsableUsedSignature OnUsed;

	// Event triggered whenever this object is used in any way (either Primary or Secondary).
	UPROPERTY(BlueprintAssignable, Meta = (DisplayName = "On Prepare For Using"), Category = "Events")
	FUsableUsedSignature OnPrepareForUsing;

	// Event triggered whenever this object is used in any way (either Primary or Secondary).
	UPROPERTY(BlueprintAssignable, Meta = (DisplayName = "On Canceled Prepare For Using"), Category = "Events")
	FUsableUsedSignature OnCanceledPrepareForUsing;

};
