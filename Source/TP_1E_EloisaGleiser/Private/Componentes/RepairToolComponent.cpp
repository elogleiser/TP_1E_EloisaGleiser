// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/Componentes/RepairToolComponent.h"
#include "Interfaces/RepairableInterface.h"
#include "DrawDebugHelpers.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Actor.h"


// Sets default values for this component's properties
URepairToolComponent::URepairToolComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	

	// ...
}


// Called when the game starts
void URepairToolComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void URepairToolComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                         FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	DetectRepairable();
	
	if (bIsRepairing)
	{
		UpdateRepair(DeltaTime);
	}

	// ...
}

void URepairToolComponent::DetectRepairable()
{
	AActor* Owner = GetOwner();

	if (!Owner)
	{
		return;
	}

	FVector Start;
	FRotator Rotation;

	Owner->GetActorEyesViewPoint(Start, Rotation);

	FVector End = Start + Rotation.Vector() * TraceDistance;
	FHitResult HitResult;

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(Owner);

	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult,Start,End,ECC_Visibility,Params);

	bool bDetectedRepairable = false;

	if (bHit)
	{
		AActor* HitActor = HitResult.GetActor();

		if (HitActor && HitActor->GetClass()->ImplementsInterface(URepairableInterface::StaticClass()))
		{
			bDetectedRepairable = true;

			if (CurrentDetectedActor != HitActor)
			{
				if (CurrentDetectedActor &&CurrentDetectedActor->GetClass()->ImplementsInterface(URepairableInterface::StaticClass()))
				{
					IRepairableInterface::Execute_OnDetectionLost(CurrentDetectedActor);
				}

				CurrentDetectedActor = HitActor;
				IRepairableInterface::Execute_OnDetected(HitActor);
			}
			}
			else
			{
				if (CurrentDetectedActor && CurrentDetectedActor->GetClass()->ImplementsInterface(URepairableInterface::StaticClass()))
				{
					IRepairableInterface::Execute_OnDetectionLost(CurrentDetectedActor);
				}

				CurrentDetectedActor = nullptr;
			}
		}
		else
		{
			if (CurrentDetectedActor &&CurrentDetectedActor->GetClass()->ImplementsInterface(URepairableInterface::StaticClass()))
			{
				IRepairableInterface::Execute_OnDetectionLost(CurrentDetectedActor);
			}

			CurrentDetectedActor = nullptr;
		}

		
	}


void URepairToolComponent::StartRepair()
{
	if (!CurrentDetectedActor)
	{
		return;
	}
	
	if (bIsRepairing)
	{
		return;
	}
	
	if (IRepairableInterface::Execute_IsRepaired(CurrentDetectedActor))
	{
		if (GEngine)
		{GEngine->AddOnScreenDebugMessage(-1,2.f,FColor::Green,TEXT("Este objeto ya fue reparado"));
		}

		return;
	}
	bIsRepairing = true;
	CurrentRepairProgress=0.f;
	CurrentRepairTarget= CurrentDetectedActor;
	
	IRepairableInterface::Execute_StartRepair(CurrentRepairTarget);
	
	
}

void URepairToolComponent::CancelRepair()
{
	if (!bIsRepairing)
	{
		return;
	}
	
	if (CurrentRepairTarget)
	{
		IRepairableInterface::Execute_CancelRepair(CurrentRepairTarget);
	}
	
	bIsRepairing = false;
	CurrentRepairProgress=0.f;
	CurrentRepairTarget = nullptr;
	
	
}


void URepairToolComponent::UpdateRepair(float DeltaTime)
{
	if (!CurrentRepairTarget)
	{
		CancelRepair();
		return;
	}
	
	if (CurrentDetectedActor != CurrentRepairTarget)
	{
		CancelRepair();
		return;
	}
	
	CurrentRepairProgress+=DeltaTime;
	
	float RequiredRepairTime = IRepairableInterface::Execute_GetRepairTime(CurrentRepairTarget);

	float ProgressPercent = CurrentRepairProgress / RequiredRepairTime;
	ProgressPercent = FMath::Clamp(ProgressPercent, 0.f, 1.f);

	OnRepairProgress.Broadcast(ProgressPercent);
	
	if (CurrentRepairProgress >= RequiredRepairTime)
	{
		CompleteRepair();
	}
}


void URepairToolComponent::CompleteRepair()
{
	if (!CurrentRepairTarget)
	{
		return;
	}
	
	FName CompletedID = IRepairableInterface::Execute_GetRepairID(CurrentRepairTarget);
	
	IRepairableInterface::Execute_CompleteRepair(CurrentRepairTarget);
	
	RepairedObjectsCodex.AddUnique(CompletedID);
	
	PrintCodex();
	
	OnRepairCompleted.Broadcast(CompletedID);
	
	bIsRepairing = false;
	CurrentRepairProgress=0.f;
	CurrentRepairTarget = nullptr;
	
	
}

void URepairToolComponent::PrintCodex() const
{
	if (!GEngine)
	{
		return;
	}
	
	FString CodexText = TEXT("CODEX - Objetos Reparados: \n");
	
	for (const FName& RepairID : RepairedObjectsCodex)
	{
		CodexText += TEXT("- ") + RepairID.ToString() + TEXT("\n");
	}
	
}
