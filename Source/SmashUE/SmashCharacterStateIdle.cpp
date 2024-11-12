// Fill out your copyright notice in the Description page of Project Settings.


#include "SmashCharacterStateIdle.h"

#include "MovieSceneCaptureProtocolBase.h"
#include "SmashCharacterStateID.h"
#include "SmashCharacterStateMachine.h"
#include "Characters/SmashCharacter.h"

ESmashCharacterStateID USmashCharacterStateIdle::GetStateID()
{
	return  ESmashCharacterStateID::Idle;
}

void USmashCharacterStateIdle::StateEnter(ESmashCharacterStateID PreviousStateID)
{
	Super::StateEnter(PreviousStateID);
	Character->PlayAnimMontage(Anim);
	Character->InputMoveXFastEvent.AddDynamic(this, &USmashCharacterStateIdle::OnInputMoveXFast);
	GEngine->AddOnScreenDebugMessage(-1,3.f,FColor::Cyan,TEXT("Enter StateIdle"));
}

void USmashCharacterStateIdle::StateExit(ESmashCharacterStateID NextStateID)
{
	Super::StateExit(NextStateID);
	Character->StopAnimMontage(Anim);
	Character->InputMoveXFastEvent.RemoveDynamic(this, &USmashCharacterStateIdle::OnInputMoveXFast);
	GEngine->AddOnScreenDebugMessage(-1,3.f,FColor::Cyan,TEXT("Exit StateIdle"));
}

void USmashCharacterStateIdle::StateTick(float DeltaTime)
{
	Super::StateTick(DeltaTime);
	
	GEngine->AddOnScreenDebugMessage(-1,0.1f,FColor::Green,TEXT("Tick StateIdle"));

	if(	FMath::Abs(Character->GetInputMoveX()) > Character->InputMoveXThreshold)
	{
		StateMachine->ChangeState(ESmashCharacterStateID::Walk);
	}
}

void USmashCharacterStateIdle::OnInputMoveXFast(float InputMoveX)
{
	StateMachine->ChangeState(ESmashCharacterStateID::Run);
}

