// Fill out your copyright notice in the Description page of Project Settings.


#include "SmashCharacterStateWalk.h"

ESmashCharacterStateID USmashCharacterStateWalk::GetStateID()
{
	return ESmashCharacterStateID::Walk;
}

void USmashCharacterStateWalk::StateEnter(ESmashCharacterStateID PreviousStateID)
{
	Super::StateEnter(PreviousStateID);
	GEngine->AddOnScreenDebugMessage(-1,3.f,FColor::Cyan,TEXT("Enter StateWalk"));
}

void USmashCharacterStateWalk::StateExit(ESmashCharacterStateID PreviousStateID)
{
	Super::StateExit(PreviousStateID);
	GEngine->AddOnScreenDebugMessage(-1,3.f,FColor::Cyan,TEXT("Exit StateWalk"));
}


