// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

class UTowerData;
/**
 * 
 */
UCLASS()
class SDINZ_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<UTowerData*> ChosenTowers;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UTowerData*> AllTowers;
};
