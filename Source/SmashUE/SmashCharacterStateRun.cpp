#include "SmashCharacterStateRun.h"

#include "SmashCharacterStateMachine.h"
#include "Characters/SmashCharacter.h"

ESmashCharacterStateID USmashCharacterStateRun::GetStateID()
{
	return ESmashCharacterStateID::Run;
}

void USmashCharacterStateRun::StateEnter(ESmashCharacterStateID PreviousStateID)
{
	Super::StateEnter(PreviousStateID);
	if(PreviousStateID == ESmashCharacterStateID::Idle)
	{
		StateMachine->ChangeState(ESmashCharacterStateID::Idle);
		return;
	}
	Character->PlayAnimMontage(Anim);
	MoveSpeedMax = RunMoveSpeedMax;
	GEngine->AddOnScreenDebugMessage(-1,3.f,FColor::Cyan,TEXT("Enter StateWalk"));
}

void USmashCharacterStateRun::StateExit(ESmashCharacterStateID PreviousStateID)
{
	Super::StateExit(PreviousStateID);
	Character->StopAnimMontage(Anim);
	GEngine->AddOnScreenDebugMessage(-1,3.f,FColor::Cyan,TEXT("Exit StateWalk"));
}

void USmashCharacterStateRun::StateTick(float DeltaTime)
{
	Super::StateTick(DeltaTime);
	Character->AddMovementInput(Character->GetActorForwardVector() * Character->GetOrientX(),  10,false);
	
	GEngine->AddOnScreenDebugMessage(-1,0.1f,FColor::Green, TEXT("Tick StateWalk"));
}

