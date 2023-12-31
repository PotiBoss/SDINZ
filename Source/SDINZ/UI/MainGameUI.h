// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainGameUI.generated.h"


class UHorizontalBox;
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
};
