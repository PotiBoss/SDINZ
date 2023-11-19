// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TowerBase.h"
#include "Engine/DataAsset.h"
#include "TowerData.generated.h"

/**
 * 
 */
UCLASS()
class SDINZ_API UTowerData : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FTowerProperties TowerProperties;
};
