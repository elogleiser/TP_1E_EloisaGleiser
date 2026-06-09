#pragma once
#include "CoreMinimal.h"
#include "RepairableData.generated.h"

USTRUCT(BlueprintType)
struct FRepairableData
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="Repair Data")
	FName RepairID = "Default ID";
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="Repair Data")
	FString DisplayName = "Repairable Object";
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="Repair Data")
	FString Description = "Object that can be repaired";
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category="Repair Data")
	float RepairTime = 3.f;
};
