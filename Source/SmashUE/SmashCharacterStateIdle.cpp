// Fill out your copyright notice in the Description page of Project Settings.


#include "SmashCharacterStateIdle.h"

#include "Characters/SmashCharacter.h"

ESmashCharacterStateID USmashCharacterStateIdle::GetStateID()
{
	return  ESmashCharacterStateID::Idle;
}

void USmashCharacterStateIdle::StateEnter(ESmashCharacterStateID PreviousStateID)
{
	Super::StateEnter(PreviousStateID);
	Character->PlayAnimMontage(Anim);
	GEngine->AddOnScreenDebugMessage(-1,3.f,FColor::Cyan,TEXT("Enter StateIdle"));
}

void USmashCharacterStateIdle::StateExit(ESmashCharacterStateID NextStateID)
{
	Super::StateExit(NextStateID);
	Character->StopAnimMontage(Anim);
	GEngine->AddOnScreenDebugMessage(-1,3.f,FColor::Cyan,TEXT("Exit StateIdle"));
}

void USmashCharacterStateIdle::StateTick(float DeltaTime)
{
	Super::StateTick(DeltaTime);
	
	GEngine->AddOnScreenDebugMessage(-1,0.1f,FColor::Green,TEXT("Tick StateIdle"));
}

