// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/CanvasPanel.h"
#include "SDINZ/TowerBase.h"
#include "TowerWidget.generated.h"

class UImage;
class UTextBlock;
class UCanvasPanel;

UCLASS()
class SDINZ_API UTowerWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void CreateTower();

	UFUNCTION(BlueprintCallable)
	void SetVars(UTowerData* Tower);
	
	UPROPERTY(BlueprintReadWrite)
	UTowerData* TowerPropertiesWidget;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* CostText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* ClassImage;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UCanvasPanel* CanvasPanel;
};
