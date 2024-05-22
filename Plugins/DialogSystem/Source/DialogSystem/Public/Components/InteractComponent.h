// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DIALOGSYSTEM_API UInteractComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UInteractComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	class UDialogParticipantComponent* CashedDialogParticipantComponent = nullptr;

	bool bCanInteract = false;

	UPROPERTY(EditAnywhere)
	float InteractDistance = 300.f;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void ClearCache();

	void UpdateCache(class UDialogParticipantComponent* InCashe);

	bool TryToInteract(class UDialogManager* DialogManager);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	float GetInteractDistance() const;

	void ScanForDialogPersonInView(FCollisionQueryParams& QueryParams);
		
};
