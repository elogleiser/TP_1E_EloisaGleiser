// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RepairToolComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRepairCompleted,FName,RepairID);
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TP_1E_ELOISAGLEISER_API URepairToolComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	URepairToolComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;


public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
	
	UFUNCTION()
	void StartRepair();
	
	UFUNCTION()
	void CancelRepair();
	
	UPROPERTY(BlueprintAssignable, Category = "Repair Events")
	FOnRepairCompleted OnRepairCompleted;
	
	UPROPERTY(VisibleAnywhere, Category = "Repair Codex", meta = (AllowPrivateAccess = "true"))
	TArray<FName> RepairedObjectsCodex;
	
private:
	
	UPROPERTY(EditAnywhere, category = "Repair", meta = (AllowPrivateAccess = "true"))
	float TraceDistance = 3000.f;
	
	UPROPERTY()
	TObjectPtr<class AActor> CurrentDetectedActor;
	
	UPROPERTY(VisibleAnywhere, Category = "Repair State", meta = (AllowPrivateAccess = "true"))
	bool bIsRepairing = false;
	
	UPROPERTY(VisibleAnywhere, Category = "Repair State", meta = (AllowPrivateAccess = "true"))
	float CurrentRepairProgress = 0.f;
	
	UPROPERTY()
	TObjectPtr<class AActor> CurrentRepairTarget;
	
	UFUNCTION()
	void DetectRepairable();

	UFUNCTION()
	void CompleteRepair();
	
	UFUNCTION()
	void UpdateRepair(float DeltaTime);
	
	UFUNCTION()
	void PrintCodex() const;
	
};
