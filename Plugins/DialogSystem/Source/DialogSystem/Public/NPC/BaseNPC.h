// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseNPC.generated.h"

UCLASS()
class DIALOGSYSTEM_API ABaseNPC : public ACharacter
{
	GENERATED_BODY()

	/** Components */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Interaction, meta = (AllowPrivateAccess = "true"))
	class UUsableComponent* UsableComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Dialog, meta = (AllowPrivateAccess = "true"))
	class UDialogManager* DialogManager;

public:
	// Sets default values for this character's properties
	ABaseNPC();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Returns UsableComponent subobject **/
	FORCEINLINE class UUsableComponent* GetUsableComponent() const { return UsableComponent; }

	/** Returns DialogManager subobject **/
	FORCEINLINE class UDialogManager* GetDialogManager() const { return DialogManager; }

};
