// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuWidget.generated.h"

USTRUCT(BlueprintType)
struct FLevelMenu
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText LevelName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* LevelThumbnail;
};


UCLASS()
class SDINZ_API UMenuWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FLevelMenu> Levels;
};
