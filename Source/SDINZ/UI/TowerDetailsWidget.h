// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TowerDetailsWidget.generated.h"

class UImage;
class UTextBlock;

UCLASS()
class SDINZ_API UTowerDetailsWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* TowerNameText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* TowerHealthText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* TowerAttackText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* TowerRangeText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* TowerAttackSpeedText;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* TowerSplash;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* TowerClass;
};
