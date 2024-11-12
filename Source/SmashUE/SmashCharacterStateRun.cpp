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
	Character->PlayAnimMontage(Anim);
	MoveSpeedMax = RunMoveSpeedMax;
	GEngine->AddOnScreenDebugMessage(-1,3.f,FColor::Cyan,TEXT("Enter StateRun"));
}

void USmashCharacterStateRun::StateExit(ESmashCharacterStateID PreviousStateID)
{
	Super::StateExit(PreviousStateID);
	Character->StopAnimMontage(Anim);
	GEngine->AddOnScreenDebugMessage(-1,3.f,FColor::Cyan,TEXT("Exit StateRun"));
}

void USmashCharacterStateRun::StateTick(float DeltaTime)
{
	Super::StateTick(DeltaTime);
	if(FMath::Abs(Character->GetInputMoveX()) < Character->InputMoveXThreshold)
	{
		StateMachine->ChangeState(ESmashCharacterStateID::Idle);
	}
	else
	{
		Character->SetOrientX(Character->GetInputMoveX());
		Character->AddMovementInput(FVector::ForwardVector,  10 * Character->GetOrientX(),false);
	}
	GEngine->AddOnScreenDebugMessage(-1,0.1f,FColor::Green, TEXT("Tick StateRun"));
}



