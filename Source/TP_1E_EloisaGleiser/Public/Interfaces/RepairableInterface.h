// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "RepairableInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class URepairableInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TP_1E_ELOISAGLEISER_API IRepairableInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Repair")
	void OnDetected();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Repair")
	void StartRepair();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Repair")
	void CancelRepair();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Repair")
	void CompleteRepair();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Repair")
	float GetRepairTime();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Repair")
	FName GetRepairID();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnDetectionLost();
};
