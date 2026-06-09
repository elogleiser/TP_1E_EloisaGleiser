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
					CurrentDetectedActor = HitActor;
					IRepairableInterface::Execute_OnDetected(HitActor);
				}
			}
			else
			{
				CurrentDetectedActor = nullptr;
			}
		}
		else
		{
			CurrentDetectedActor = nullptr;
		}

		DrawDebugLine(GetWorld(),Start,End,bDetectedRepairable ? FColor::Green : FColor::Red,false,1.f,0,2.f);
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
	
	bIsRepairing = true;
	CurrentRepairProgress=0.f;
	CurrentRepairTarget= CurrentDetectedActor;
	
	IRepairableInterface::Execute_StartRepair(CurrentRepairTarget);
	
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1,0,FColor::Green,TEXT("Reparacion Iniciada"));
	}
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
	
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1,0,FColor::Green,TEXT("Reparacion Cancelada"));
	}
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
	
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1,0,FColor::Cyan,TEXT("Progreso: ")+FString::SanitizeFloat(CurrentRepairProgress));
	}
	
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
	IRepairableInterface::Execute_CompleteRepair(CurrentRepairTarget);
	
	bIsRepairing = false;
	CurrentRepairProgress=0.f;
	CurrentRepairTarget = nullptr;
	
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1,2.f,FColor::Green, TEXT("Reparacion Completada"));
	}
}
