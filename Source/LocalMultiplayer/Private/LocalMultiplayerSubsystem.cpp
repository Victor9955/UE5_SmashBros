// Fill out your copyright notice in the Description page of Project Settings.


#include "LocalMultiplayerSubsystem.h"

#include "EnhancedInputSubsystems.h"
#include "GameFramework/PlayerInput.h"
#include "Kismet/GameplayStatics.h"

void ULocalMultiplayerSubsystem::CreateInitPlayers(ELocalMultiplyareInputMappingType MappingType)
{
	const ULocalMultiplayerSettings* Settings = GetDefault<ULocalMultiplayerSettings>();
	for (int i = 0; i < Settings->GetNbKeyboardProfiles() + Settings->NbMaxGamepad; ++i)
	{
		UGameplayStatics::CreatePlayer(GetWorld(),i, true)->AutoReceiveInput;
	}
}

int ULocalMultiplayerSubsystem::GetAssignedPlayerIndexFromKeyboardProfileIndex(int KeyboardProfileIndex)
{
	if(PlayerIndexFromKeyboardProfileIndex.Contains(KeyboardProfileIndex))
	{
		return PlayerIndexFromKeyboardProfileIndex[KeyboardProfileIndex];
	}
	return -1;
}

int ULocalMultiplayerSubsystem::AssignNewPlayerToKeyboardProfile(int KeyboardProfileIndex)
{
	const ULocalMultiplayerSettings* Settings = GetDefault<ULocalMultiplayerSettings>();
	if(LastAssignedPlayerIndex >= Settings->GetNbKeyboardProfiles() + Settings->NbMaxGamepad) return -1;
	PlayerIndexFromKeyboardProfileIndex.Add(KeyboardProfileIndex,LastAssignedPlayerIndex);
	LastAssignedPlayerIndex++;
	return LastAssignedPlayerIndex - 1;
}

void ULocalMultiplayerSubsystem::AssignKeyboardMapping(int PlayerIndex, int KeyboardProfileIndex,
	ELocalMultiplyareInputMappingType MappingType) const
{
	const ULocalMultiplayerSettings* Settings = GetDefault<ULocalMultiplayerSettings>();

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(),PlayerIndex);
	if(PlayerController == nullptr) return;
	
	PlayerController->GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>()->AddMappingContext(Settings->KeyboardProfilesData[KeyboardProfileIndex].GetIMCFromType(MappingType), 0);
	
}

int ULocalMultiplayerSubsystem::GetAssignedPlayerIndexFromGamepadDeviceID(int DeviceID)
{
	if(PlayerIndexFromGamepadDeviceID.Contains(DeviceID))
	{
		return PlayerIndexFromGamepadDeviceID[DeviceID];
	}
	return -1;
}

int ULocalMultiplayerSubsystem::AssignNewPlayerToGamepadDeviceID(int DeviceID)
{
	const ULocalMultiplayerSettings* Settings = GetDefault<ULocalMultiplayerSettings>();
	if(LastAssignedPlayerIndex >= Settings->GetNbKeyboardProfiles() + Settings->NbMaxGamepad) return -1;
	PlayerIndexFromGamepadDeviceID.Add(DeviceID,LastAssignedPlayerIndex);
	LastAssignedPlayerIndex++;
	return LastAssignedPlayerIndex - 1;
}

void ULocalMultiplayerSubsystem::AssignGamepadInputMapping(int PlayerIndex,
	ELocalMultiplyareInputMappingType MappingType) const
{
	const ULocalMultiplayerSettings* Settings = GetDefault<ULocalMultiplayerSettings>();

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(),PlayerIndex);
	if(PlayerController == nullptr) return;
	
	PlayerController->GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>()->AddMappingContext(Settings->GamepadProfileData.GetIMCFromType(MappingType), 0);
}
