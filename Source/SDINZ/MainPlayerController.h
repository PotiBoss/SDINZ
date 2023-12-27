// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TowerBase.h"
#include "GameFramework/PlayerController.h"
#include "UI/TowerWidget.h"
#include "MainPlayerController.generated.h"

class AGrid;
class UMainGameUI;
class UTowerData;
class AMainPlayer;

/**
 * 
 */
UCLASS()
class SDINZ_API AMainPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	AGrid* GetGrid() { return Grid; }

	UPROPERTY()
	FVector CurrentTileLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTowerData* CurrentTower;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ATowerBase* PreviewTower;
	
	UPROPERTY(BlueprintReadWrite)
	AMainPlayer* MainPlayer;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Energy = 5.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float EnergyGain = 1.f;
	
protected:
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;

	virtual void BeginPlay() override;

	UFUNCTION()
	void OnMousePress();

	UFUNCTION()
	void OnMouseRelease();

	UPROPERTY()
	AGrid* Grid;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UTowerData*> AvailableTowers;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite)
	TArray<UTowerWidget*> TowerWidgets; 
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> MainUIClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> TowerWidgetClass;

	UPROPERTY(BlueprintReadWrite)
	UMainGameUI* MainUI;
};
