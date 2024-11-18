// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraWorldSubsystem.h"

#include "Kismet/GameplayStatics.h"

void UCameraWorldSubsystem::PostInitialize()
{
	
}



void UCameraWorldSubsystem::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);
	CameraMain = FindCameraByTag("CameraMain");
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

void UCameraWorldSubsystem::AddFollowTarget(AActor* FollowTarget)
{
	FollowTargets.Add(FollowTarget);
}

void UCameraWorldSubsystem::RemoveFollowTarget(AActor* FollowTarget)
{
	FollowTargets.Remove(FollowTarget);
}

void UCameraWorldSubsystem::TickUpdateCameraPosition(float DeltaTime)
{
	FVector NewLocation = CalculateAveragePositionBetweenTargets();
	GEngine->AddOnScreenDebugMessage(-1,3.f,FColor::Cyan,FString::Printf(TEXT("Tick Camera = %f"), CameraMain->GetAttachmentRootActor()->GetActorLocation().Z));
	if(CameraMain != nullptr)
	{
		CameraMain->SetWorldLocation(FVector(NewLocation.X,CameraMain->GetAttachmentRootActor()->GetActorLocation().Y,NewLocation.Z));
	}
}

FVector UCameraWorldSubsystem::CalculateAveragePositionBetweenTargets()
{
	FVector result;
	float x = FollowTargets[0]->GetActorLocation().X;
	float z = FollowTargets[0]->GetActorLocation().Z;

	for(int i = 1; i < FollowTargets.Num(); i++)
	{
		x += FollowTargets[i]->GetActorLocation().X;
		z += FollowTargets[i]->GetActorLocation().Z;
	}

	x /= FollowTargets.Num();
	z /= FollowTargets.Num();
	return FVector(x,0, z);
}

UCameraComponent* UCameraWorldSubsystem::FindCameraByTag(const FName& Tag) const
{
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), FoundActors);
	for(AActor* Actor : FoundActors)
	{
		for(UActorComponent* Comp : Actor->GetComponents())
		{
			if(Cast<UCameraComponent>(Comp) != nullptr)
			{
				return Cast<UCameraComponent>(Comp);
			}
		}
	}
	return nullptr;	
}