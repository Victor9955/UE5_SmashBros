#include "SmashCharacterStateFall.h"

#include "SmashCharacterStateMachine.h"
#include "Characters/SmashCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

ESmashCharacterStateID USmashCharacterStateFall::GetStateID()
{
	return ESmashCharacterStateID::Fall;
}

void USmashCharacterStateFall::StateEnter(ESmashCharacterStateID PreviousStateID)
{
	Super::StateEnter(PreviousStateID);
	GEngine->AddOnScreenDebugMessage(-1,3.f,FColor::Cyan,TEXT("Enter StateFall"));
}

void USmashCharacterStateFall::StateExit(ESmashCharacterStateID NextStateID)
{
	Super::StateExit(NextStateID);
	GEngine->AddOnScreenDebugMessage(-1,3.f,FColor::Cyan,TEXT("Exit StateFall"));
}

void USmashCharacterStateFall::StateTick(float DeltaTime)
{
	Super::StateTick(DeltaTime);
	if(Character->GetCharacterMovement()->IsMovingOnGround())
	{
		StateMachine->ChangeState(ESmashCharacterStateID::Idle);
	}
	GEngine->AddOnScreenDebugMessage(-1,3.f,FColor::Cyan,TEXT("Tick StateFall"));
}
