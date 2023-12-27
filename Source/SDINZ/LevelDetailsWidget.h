// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LevelDetailsWidget.generated.h"

/**
 * 
 */
UCLASS()
class SDINZ_API ULevelDetailsWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* LevelName;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UImage* LevelThumbnail;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* StartButton;
};
