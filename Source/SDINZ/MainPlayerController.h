// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TowerBase.h"
#include "GameFramework/PlayerController.h"
#include "MainPlayerController.generated.h"

class AGrid;

/**
 * 
 */
UCLASS()
class SDINZ_API AMainPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AGrid* GetGrid() { return Grid; }

	UPROPERTY()
	FVector CurrentTileLocation;
	
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
	TSubclassOf<ATowerBase> TowerClass;
};
