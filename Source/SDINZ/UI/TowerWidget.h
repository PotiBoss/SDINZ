// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SDINZ/TowerBase.h"
#include "TowerWidget.generated.h"

class UTextBlock;

UCLASS()
class SDINZ_API UTowerWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void CreateTower();
	
	UPROPERTY(BlueprintReadWrite)
	FTowerProperties TowerPropertiesWidget;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* CostText;
};
