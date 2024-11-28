// Fill out your copyright notice in the Description page of Project Settings.


#include "LocalMultiplayerGameViewportClient.h"

#include "LocalMultiplayerSubsystem.h"
#include "GameFramework/PlayerInput.h"
#include "Kismet/GameplayStatics.h"

void ULocalMultiplayerGameViewportClient::PostInitProperties()
{
	Super::PostInitProperties();
	MaxSplitscreenPlayers = 8;
}

bool ULocalMultiplayerGameViewportClient::InputKey(const FInputKeyEventArgs& EventArgs)
{
	const ULocalMultiplayerSettings* Settings = GetDefault<ULocalMultiplayerSettings>();
	int ProfileIndex = Settings->FindKeyboardProfileIndexFromKey(EventArgs.Key, InGame);
	if(ProfileIndex != -1)
	{
		ULocalMultiplayerSubsystem* Subsystem = GetGameInstance()->GetSubsystem<ULocalMultiplayerSubsystem>();
		if(Subsystem == nullptr) return false;
		int PlayerIndex = Subsystem->GetAssignedPlayerIndexFromKeyboardProfileIndex(ProfileIndex);
		if(PlayerIndex == -1)
		{
			Subsystem->AssignNewPlayerToKeyboardProfile(ProfileIndex);
		}
		Subsystem->AssignKeyboardMapping(PlayerIndex,ProfileIndex,InGame);
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(),PlayerIndex);
		if(PlayerController == nullptr) return false;
		GEngine->AddOnScreenDebugMessage(-1,3.f,FColor::Cyan,FString::Printf(TEXT("Input %d"),PlayerIndex));
		PlayerController->InputKey(
			FInputKeyParams(
				EventArgs.Key,
				EventArgs.Event,
				EventArgs.AmountDepressed
				));
		return true;
	}
	return false;
}

bool ULocalMultiplayerGameViewportClient::InputAxis(FViewport* m_Viewport, FInputDeviceId InputDevice, FKey Key,
	float Delta, float DeltaTime, int32 NumSamples = 1, bool bGamepad = false)
{
	ULocalMultiplayerSubsystem* Subsystem = GetGameInstance()->GetSubsystem<ULocalMultiplayerSubsystem>();
	if(Subsystem == nullptr) return false;
	int PlayerIndex = Subsystem->GetAssignedPlayerIndexFromGamepadDeviceID(InputDevice.GetId());
	if(PlayerIndex == -1)
	{
		Subsystem->AssignNewPlayerToGamepadDeviceID(InputDevice.GetId());
	}
	Subsystem->AssignGamepadInputMapping(PlayerIndex,InGame);
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(),PlayerIndex);
	if(PlayerController == nullptr) return false;
	UGameplayStatics::GetPlayerController(GetWorld(),PlayerIndex)->InputKey(
			FInputKeyParams(Key,
				Delta,
				DeltaTime,
				NumSamples
				));
	return true;
}
