// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SmashCharacterState.h"
#include "SmashCharacterStateJump.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SMASHUE_API USmashCharacterStateJump : public USmashCharacterState
{
public:
	virtual ESmashCharacterStateID GetStateID() override;
	virtual void StateEnter(ESmashCharacterStateID PreviousStateID) override;
	virtual void StateExit(ESmashCharacterStateID NextStateID) override;
	virtual void StateTick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	float JumpMaxHeight = 400;
	UPROPERTY(EditAnywhere)
	float JumpDuration = 280;
	UPROPERTY(EditAnywhere)
	float JumpWalkSpeed = 1;
	UPROPERTY(EditAnywhere)
	float JumpAirControl = 1;
	

private:
	GENERATED_BODY()
	float JumpTimer;
};
