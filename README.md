# DialogSystem

A test task, where I tried to implement a DialogManager via Plugin for UE5.4.1.

This is a small project where I used it.

NOTE: to check for a gamepad usage, there is a CommonInput plugin, so firstly enable it in Engine. Else Remove it from Build.cs file and in Include from ThirdPersonCharacter.cpp

All Sources of DialogManager are located in Plugins/DialogManager.

## Plugin Usage
To use a plugin move it to Plugins folder and enable it in Engine->Plugins.

After it add it to Build.cs:
```
PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "CommonInput", "DialogSystem" });
```

In result, now you can use DialogComponents and UI classes.

## UDialogManager
It is a main component, which will proccess all dialogs. It is used by a PlayerCharacter.

All functionality is working on C++, for Blueprints there is only 2 possible events, which you can implement: ***On Start Dialog***, ***On End Dialog***

In example project it`s used for a UI creation.

## UDialogParticipantComponent
This component was created for NPCs. You can simply add it to NPC, choose a Dialog DataTable for this Character. That is all.

But DataTable must have a SentenceRow type.

## DialogDataTable
To store a dialog, and to use it, you need to create a DataTable from SentenceRow.

NOTE: First sentence must have a START name!

For each sentence you can choose a speaker name, text, type(default sentence or maybe it must be a response with some answers). On Response type add variants for responses. Mark sentence if it is an end for dialog. Also each sentence must have a name for next sentence. On other way, dialog will end.

## UInteractComponent
Interact Compomponent is looking for Characters, can the be a Participant or no, if yes you can interact and speak with them.

To use it, add it to your PlayerCharacter, and Scan other characters(use it in TickComponent):
```
void ATestTaskCharacter::InteractTickScan()
{
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);

	InteractComponent->ScanForDialogPersonInView(QueryParams);
}
```

To interact ***On Button Pressed Event***, or on input actions, use:
```
InteractComponent->TryToInteract(DialogManager)
```
If interaction is successed, returns true. After this Dialog Starts.

## UI
To use UI for dialogs, you need to create a ***WB_GeneralDialog***. After creation you need to Initialize it(use a Blueprit Node). For initialization you need a DialogManager and a bool, which represents a gamepad usage. After it you can add it to viewport.