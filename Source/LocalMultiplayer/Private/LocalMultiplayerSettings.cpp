// Fill out your copyright notice in the Description page of Project Settings.


#include "LocalMultiplayerSettings.h"

bool FLocalMultiplayerProfileData::ContainsKey(const FKey& Key, ELocalMultiplyareInputMappingType MappingType) const
{
	if(MappingType == Menu)
	{
		for(FEnhancedActionKeyMapping KeyMapping : IMCMenu->GetMappings())
		{
			if(Key == KeyMapping.Key)
			{
				return true;
			}
		}
		return false;
	}
	else if(MappingType == InGame)
	{
		for(FEnhancedActionKeyMapping KeyMapping : IMCGame->GetMappings())
		{
			if(Key == KeyMapping.Key)
			{
				return true;
			}
		}
		return false;
	}
	return false;
}

UInputMappingContext* FLocalMultiplayerProfileData::GetIMCFromType(ELocalMultiplyareInputMappingType MappingType) const
{
	if(MappingType == Menu)
	{
		return IMCMenu;
	}
	else if(MappingType == InGame)
	{
		return IMCGame;
	}
	return IMCGame;
}

int ULocalMultiplayerSettings::GetNbKeyboardProfiles() const
{
	return KeyboardProfilesData.Num();
}

int ULocalMultiplayerSettings::FindKeyboardProfileIndexFromKey(const FKey& Key,ELocalMultiplyareInputMappingType MappingType) const
{
	for (int i = 0; i < KeyboardProfilesData.Num(); ++i)
	{
		if(KeyboardProfilesData[i].ContainsKey(Key, MappingType))
		{
			return i;
		}
	}
	return -1;
}
