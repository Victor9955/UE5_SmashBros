// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MatchGameMode.generated.h"


class UInputMappingContext;
class USmashCharacterInputData;
class USmashCharacterInputData;
class ASmashCharacter;
class AArenaPlayerStart;

/**
 * 
 */
UCLASS()
class SMASHUE_API AMatchGameMode : public AGameModeBase
{
	GENERATED_BODY()

	public:
		virtual void BeginPlay() override;
	private:

		void CreateAndInitPlayers() const;
		USmashCharacterInputData* LoadInputDataFromConfig();

		UInputMappingContext* LoadInputMappingContextFromConfig();
	
		void FindPlayerStartActorsInArena(TArray<AArenaPlayerStart*>& ResultActors);
		TSubclassOf<ASmashCharacter> GetSmashCharacterClassFromInputType(EAutoReceiveInput::Type InputType) const;
		void SpawnCharacters(const TArray<AArenaPlayerStart*>& SpawnPoints);
	protected:
		UPROPERTY()
		TArray<ASmashCharacter*> CharactersInsideArena;
};
