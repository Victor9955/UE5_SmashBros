// Fill out your copyright notice in the Description page of Project Settings.


#include "SmashCharacterStateJump.h"

#include "SmashCharacterStateMachine.h"
#include "Characters/SmashCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"


ESmashCharacterStateID USmashCharacterStateJump::GetStateID()
{
	return ESmashCharacterStateID::Jump;
}

void USmashCharacterStateJump::StateEnter(ESmashCharacterStateID PreviousStateID)
{
	Super::StateEnter(PreviousStateID);
	
	Character->GetCharacterMovement()->GravityScale = ((-2.f * JumpMaxHeight) / FMathf::Pow((JumpDuration / 2.f), 2)) / -981.f;
	Character->GetCharacterMovement()->JumpZVelocity = ((2.f * JumpMaxHeight) / (JumpDuration / 2.f));
	Character->Jump();
	Character->GetCharacterMovement()->MaxWalkSpeed *= JumpAirControl; 
	GEngine->AddOnScreenDebugMessage(-1,3.f,FColor::Cyan,TEXT("Enter StateJump"));
}

void USmashCharacterStateJump::StateExit(ESmashCharacterStateID NextStateID)
{
	Super::StateExit(NextStateID);
	GEngine->AddOnScreenDebugMessage(-1,3.f,FColor::Cyan,TEXT("Exit StateJump"));
}

void USmashCharacterStateJump::StateTick(float DeltaTime)
{
	Super::StateTick(DeltaTime);
	GEngine->AddOnScreenDebugMessage(-1,3.f,FColor::Cyan,TEXT("Tick StateJump"));
	
	if(Character->GetCharacterMovement()->Velocity.Z < 0)
	{
		Character->StopJumping();
		StateMachine->ChangeState(ESmashCharacterStateID::Fall);
	}
	
	if(FMath::Abs(Character->GetInputMoveX()) >= Character->InputMoveXThreshold)
	{
		Character->AddMovementInput(FVector::ForwardVector,Character->GetOrientX());
	}
}
