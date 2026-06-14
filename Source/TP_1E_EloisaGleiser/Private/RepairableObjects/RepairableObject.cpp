// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/RepairableObjects/RepairableObject.h"


// Sets default values
ARepairableObject::ARepairableObject()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;
}

// Called when the game starts or when spawned
void ARepairableObject::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARepairableObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ARepairableObject::OnDetected_Implementation()
{
	if (bRepaired)
	{
		return;
	}
	
	if (Mesh && DetectedMaterial)
	{
		Mesh->SetMaterial(0, DetectedMaterial);
	}
	
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1,2.f,FColor::Orange,TEXT("Objeto detectado: ") + RepairData.DisplayName + TEXT("\n Presione la ´E´ para reparar"));
	}
	
	
}

void ARepairableObject::StartRepair_Implementation()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1,2.f,FColor::Yellow,TEXT("Comenzando reparacion de: ") + RepairData.DisplayName);
	}
	
	
}

void ARepairableObject::CancelRepair_Implementation()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1,2.f,FColor::Red,TEXT("Reparacion cancelada de: ") + RepairData.DisplayName);
	}
	
}

void ARepairableObject::CompleteRepair_Implementation()
{
	bRepaired = true;
	if (Mesh && RepairedMaterial)
	{
		Mesh->SetMaterial(0, RepairedMaterial);
	}
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1,2.f,FColor::Green, TEXT("Se reparo exitosamente: ") + RepairData.DisplayName);
	}
	
}
float ARepairableObject::GetRepairTime_Implementation()
{
	return RepairData.RepairTime;
}

FName ARepairableObject::GetRepairID_Implementation()
{
	return RepairData.RepairID;
}

void ARepairableObject::OnDetectionLost_Implementation()
{
	if (bRepaired)
	{
		return;
	}

	if (Mesh && DefaultMaterial)
	{
		Mesh->SetMaterial(0, DefaultMaterial);
	}
}

