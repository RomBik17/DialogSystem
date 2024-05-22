// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DialogManager.generated.h"

UENUM(BlueprintType)
enum class ESentenceType : uint8
{
	Default,
	Response
};

USTRUCT(BlueprintType)
struct DIALOGSYSTEM_API FResponseData
{

	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText ShortSentenceTextForDialogButton;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName SentenceRowName;

};

USTRUCT(BlueprintType)
struct DIALOGSYSTEM_API FSentenceRow : public FTableRowBase
{

	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText SpeakerName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ESentenceType SentenceType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText SentenceText;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool LastSentence = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName NextSentenceName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FResponseData> Responses;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEndDialog);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSentenceUpdate, FText, Sentence);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FResponseUpdate, const TArray<FResponseData>&, Responses);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DIALOGSYSTEM_API UDialogManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDialogManager();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool RememberDialogProgress = false;

	FText CreateSentence(FSentenceRow* SentenceRow);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (RequiredAssetDataTags = "RowStructure=/Script/DialogSystem.SentenceRow"))
	UDataTable* DialogTable;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName StartSentence = "START";

	FSentenceRow* CurrentSentence = nullptr;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void BeginConversation();

	UFUNCTION(BlueprintCallable)
	void EndConversation();

	void ProcessDialogRow(FName SentenceName);

	UFUNCTION(BlueprintCallable)
	void TryProcessNextDialogRow();

	UFUNCTION(BlueprintCallable)
	void TryProcessNextDialogRowAfterResponse(FName SentenceRowName);

	UPROPERTY(BlueprintAssignable, Meta = (DisplayName = "On End Dialog"), Category = "Events")
	FEndDialog EndDialog;

	UPROPERTY(BlueprintAssignable, Meta = (DisplayName = "On Sentence Updated"), Category = "Events")
	FSentenceUpdate OnSentenceUpdated;

	UPROPERTY(BlueprintAssignable, Meta = (DisplayName = "On Response Updated"), Category = "Events")
	FResponseUpdate OnResponseUpdated;
};
