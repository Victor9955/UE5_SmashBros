// Fill out your copyright notice in the Description page of Project Settings.


#include "Match/MatchGameMode.h"
#include "Arena/ArenaPlayerStart.h"
#include "Kismet/GameplayStatics.h"

void AMatchGameMode::BeginPlay()
{
	Super::BeginPlay();

	TArray<AArenaPlayerStart*> PlayerStartPoints;
	FindPlayerStartActorsInArena(PlayerStartPoints);

	for(AArenaPlayerStart* PlayerStartPoint : PlayerStartPoints)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Cyan, PlayerStartPoint->GetFName().ToString());
	}
}


void AMatchGameMode::FindPlayerStartActorsInArena(TArray<AArenaPlayerStart*>& ResultActors)
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AArenaPlayerStart::StaticClass(), FoundActors);

	for (int i = 0; i < FoundActors.Num(); i++)
	{
		AArenaPlayerStart* ArenaPlayerStartActor = Cast<AArenaPlayerStart, AActor>(FoundActors[i]);
		if(ArenaPlayerStartActor == nullptr) continue;

		ResultActors.Add(ArenaPlayerStartActor);
	}
}

