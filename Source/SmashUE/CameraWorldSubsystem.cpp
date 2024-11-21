// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraWorldSubsystem.h"

#include "CameraFollowTarget.h"
#include "Kismet/GameplayStatics.h"

void UCameraWorldSubsystem::PostInitialize()
{
	
}



void UCameraWorldSubsystem::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);
	CameraMain = FindCameraByTag(FName(TEXT("CameraMain")));

	AActor* CameraBoundsActor = FindCameraBoundsActor();
	if (CameraBoundsActor != nullptr)
	{
		InitCamerabounds(CameraBoundsActor);
	}
}

void UCameraWorldSubsystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(FollowTargets.Num() > 0)
	{
		TickUpdateCameraPosition(DeltaTime);
	}
}

TStatId UCameraWorldSubsystem::GetStatId() const
{
	return TStatId();
}

void UCameraWorldSubsystem::AddFollowTarget(UObject* FollowTarget)
{
	ICameraFollowTarget* Cash = Cast<ICameraFollowTarget>(FollowTarget);
	if(Cash != nullptr && Cash->IsFollowable())
	{
		FollowTargets.Add(FollowTarget);
	}
}

void UCameraWorldSubsystem::RemoveFollowTarget(UObject* FollowTarget)
{
	FollowTargets.Remove(FollowTarget);
}

void UCameraWorldSubsystem::TickUpdateCameraPosition(float DeltaTime)
{
	FVector NewLocation = CalculateAveragePositionBetweenTargets();
	ClampPositionIntoCameraBounds(NewLocation);
	if(CameraMain != nullptr)
	{
		CameraMain->SetWorldLocation(FVector(NewLocation.X,CameraMain->GetAttachmentRootActor()->GetActorLocation().Y,NewLocation.Z));
	}
}

FVector UCameraWorldSubsystem::CalculateAveragePositionBetweenTargets()
{
	FVector result = FVector::ZeroVector;

	for(int i = 0; i < FollowTargets.Num(); i++)
	{
		ICameraFollowTarget* Cash = Cast<ICameraFollowTarget>(FollowTargets[i]);
		if(Cash != nullptr && Cash->IsFollowable())
		{
			result += Cash->GetFollowPosition();
		}
	}
	
	result /= FollowTargets.Num();
	return FVector(result.X,0, result.Z);
}

AActor* UCameraWorldSubsystem::FindCameraBoundsActor()
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName(TEXT("CameraBounds")), FoundActors);
	if(FoundActors.Num() > 0)
	{
		return FoundActors[0];
	}
	return nullptr;	
}

void UCameraWorldSubsystem::InitCamerabounds(AActor* CameraBoundsActor)
{
	FVector BoundsCenter;
	FVector BoundsExtends;
	CameraBoundsActor->GetActorBounds(false, BoundsCenter, BoundsExtends);

	CameraBoundsMin.X = BoundsCenter.X - BoundsExtends.X / 2;
	CameraBoundsMin.Y = BoundsCenter.Z - BoundsExtends.Z / 2;
	CameraBoundsMax.X = BoundsCenter.X + BoundsExtends.X / 2;
	CameraBoundsMax.Y = BoundsCenter.Z + BoundsExtends.Z / 2;
	CameraBoundsYProjectionCenter = BoundsCenter.Y;
}

void UCameraWorldSubsystem::ClampPositionIntoCameraBounds(FVector& Position)
{
	FVector2D ViewPortBoundsMin, ViewPortBoundsMax;
	GetViewportBounds(ViewPortBoundsMin, ViewPortBoundsMax);

	FVector WorldBoundsMin = CalculateWorldPositionFromViewportPosition(ViewPortBoundsMin);
	FVector WorldBoundsMax = CalculateWorldPositionFromViewportPosition(ViewPortBoundsMax);

	GEngine->AddOnScreenDebugMessage(-1,3.f,FColor::Blue,FString::Printf(TEXT("Camera Bound X %f"),CameraBoundsMin.X));
	GEngine->AddOnScreenDebugMessage(-1,3.f,FColor::Blue,FString::Printf(TEXT("Camera Bound Y %f"),CameraBoundsMin.Y));
	GEngine->AddOnScreenDebugMessage(-1,3.f,FColor::Blue,FString::Printf(TEXT("World Bound X %f"),WorldBoundsMin.X));
	GEngine->AddOnScreenDebugMessage(-1,3.f,FColor::Blue,FString::Printf(TEXT("World Bound Y %f"),WorldBoundsMin.Z));
	
	float WorldBoundsSizeX = WorldBoundsMax.X - WorldBoundsMin.X;
	float WorldBoundsSizeY = WorldBoundsMax.Z - WorldBoundsMin.Z;

	
	Position.X = FMathf::Clamp(Position.X, CameraBoundsMin.X + (WorldBoundsSizeX / 2.f), CameraBoundsMax.X - (WorldBoundsSizeX / 2.f));
	Position.Z = FMathf::Clamp(Position.Z, CameraBoundsMin.Y + (WorldBoundsSizeY / 2.f), CameraBoundsMax.Y - (WorldBoundsSizeY / 2.f));
}

void UCameraWorldSubsystem::GetViewportBounds(FVector2D& OutViewportBoundsMin, FVector2D& OutViewportBoundsMax)
{
	UGameViewportClient* ViewportClient = GetWorld()->GetGameViewport();
	if(ViewportClient != nullptr) return;

	FViewport* Viewport = ViewportClient->Viewport;
	if(Viewport != nullptr) return;

	FIntRect ViewRect(
		Viewport->GetInitialPositionXY(),
		Viewport->GetInitialPositionXY() + Viewport->GetSizeXY()
		);
	FIntRect ViewportRect = Viewport->CalculateViewExtents(CameraMain->AspectRatio, ViewRect);

	OutViewportBoundsMin.X = ViewportRect.Min.X;
	OutViewportBoundsMin.Y = ViewportRect.Min.Y;
	OutViewportBoundsMax.X = ViewportRect.Max.X;
	OutViewportBoundsMax.Y = ViewportRect.Max.Y;
}

FVector UCameraWorldSubsystem::CalculateWorldPositionFromViewportPosition(const FVector2D& ViewportPosition)
{
	if(CameraMain == nullptr) return FVector::ZeroVector;

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if(PlayerController == nullptr) return FVector::ZeroVector;

	float YDistanceToCenter = CameraMain->GetOwner()->GetActorLocation().Y - CameraBoundsYProjectionCenter;

	FVector CameraWorldProjectionDir;
	FVector WorldPosition;
	UGameplayStatics::DeprojectScreenToWorld(
		PlayerController,
		ViewportPosition,
		WorldPosition,
		CameraWorldProjectionDir);

	WorldPosition += CameraWorldProjectionDir * YDistanceToCenter;
	
	return WorldPosition;
}

UCameraComponent* UCameraWorldSubsystem::FindCameraByTag(const FName& Tag) const
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(),Tag,FoundActors);
	for(UActorComponent* Comp : FoundActors[0]->GetComponents())
	{
		UCameraComponent* Cash = Cast<UCameraComponent>(Comp);
		if(Cash!= nullptr)
		{
			return Cash;
		}
	}
	return nullptr;	
}
