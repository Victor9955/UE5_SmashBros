// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "InputMappingContext.h"
#include "LocalMultiplayerSettings.generated.h"

UENUM()
enum ELocalMultiplyareInputMappingType
{
	InGame,
	Menu
};


USTRUCT()
struct FLocalMultiplayerProfileData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	FName ProfileName;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UInputMappingContext> IMCGame;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UInputMappingContext> IMCMenu;

	bool ContainsKey(const FKey& Key, ELocalMultiplyareInputMappingType MappingType) const;

	UInputMappingContext* GetIMCFromType(ELocalMultiplyareInputMappingType MappingType) const;
};



/**
 * 
 */
UCLASS(Config = Game,DefaultConfig,meta = (DisplayName = "Local Multiplayer Settings"))
class LOCALMULTIPLAYER_API ULocalMultiplayerSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UPROPERTY(Config, EditAnywhere, Category = "LocalMultiplayer")
	TArray<FLocalMultiplayerProfileData> KeyboardProfilesData;

	int GetNbKeyboardProfiles() const;

	int FindKeyboardProfileIndexFromKey(const FKey& Key, ELocalMultiplyareInputMappingType MappingType) const;

	UPROPERTY(Config, EditAnywhere, Category = "LocalMultiplayer")
	FLocalMultiplayerProfileData GamepadProfileData;

	UPROPERTY(Config, EditAnywhere, Category = "LocalMultiplayer")
	int NbMaxGamepad = 4;
};
