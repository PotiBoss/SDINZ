// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainGameUI.generated.h"


class UHorizontalBox;
class UProgressBar;
class UTextBlock;
/**
 * 
 */
UCLASS()
class SDINZ_API UMainGameUI : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UHorizontalBox* TowerHorizontalBox;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UProgressBar* EnergyBar;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* EnemiesText;
	
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* HealthText;
};
