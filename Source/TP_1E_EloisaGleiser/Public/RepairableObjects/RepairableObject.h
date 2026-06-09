// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/RepairableInterface.h"
#include "Structs/RepairableData.h"
#include "RepairableObject.generated.h"


UCLASS()
class TP_1E_ELOISAGLEISER_API ARepairableObject : public AActor, public IRepairableInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ARepairableObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	virtual void OnDetected_Implementation() override;
	virtual void StartRepair_Implementation() override;
	virtual void CancelRepair_Implementation() override;
	virtual void CompleteRepair_Implementation() override;
	virtual float GetRepairTime_Implementation() override;
	virtual FName GetRepairID_Implementation() override;
private:
	UPROPERTY(EditAnywhere, category = "Repair", meta = (AllowPrivateAccess = "true"))
	FRepairableData RepairData;
	
	UPROPERTY(EditAnywhere, category = "Repair", meta = (AllowPrivateAccess = "true"))
	bool bRepaired=false;
};
