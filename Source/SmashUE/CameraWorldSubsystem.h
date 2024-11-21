// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "Subsystems/WorldSubsystem.h"
#include "CameraWorldSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class SMASHUE_API UCameraWorldSubsystem : public UTickableWorldSubsystem
{
	GENERATED_BODY()
#pragma region Subsystem Overrides
public:
	virtual void PostInitialize() override;
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;
	virtual void Tick(float DeltaTime) override;
	virtual TStatId GetStatId() const override;
#pragma endregion
#pragma region Follow Targets
	void AddFollowTarget(UObject* FollowTarget);
	void RemoveFollowTarget(UObject* FollowTarget);
protected:

	UPROPERTY()
	TArray<UObject*> FollowTargets;
#pragma endregion
#pragma region Main Camera
	UPROPERTY()
	TObjectPtr<UCameraComponent> CameraMain;
	UCameraComponent* FindCameraByTag(const FName& Tag) const;

#pragma endregion
#pragma region Misc
	void TickUpdateCameraPosition(float DeltaTime);
	FVector CalculateAveragePositionBetweenTargets();
#pragma endregion
#pragma region Bounds

	protected:
	UPROPERTY()
	FVector2D CameraBoundsMin;

	UPROPERTY()
	FVector2D CameraBoundsMax;

	UPROPERTY()
	float CameraBoundsYProjectionCenter;

	AActor* FindCameraBoundsActor();
	void InitCamerabounds(AActor* CameraBoundsActor);
	void ClampPositionIntoCameraBounds(FVector& Position);
	void GetViewportBounds(FVector2D& OutViewportBoundsMin, FVector2D& OutViewportBoundsMax);
	FVector CalculateWorldPositionFromViewportPosition(const FVector2D& ViewportPosition);
#pragma endregion
};
