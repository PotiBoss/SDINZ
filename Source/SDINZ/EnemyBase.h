// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "EnemyBase.generated.h"

class AMainPlayerController;
class ATowerController;
class ASplineMeshActor;
class ARoute;

/**
 * 
 */
UCLASS()
class SDINZ_API AEnemyBase : public APaperCharacter
{
	GENERATED_BODY()

public:
	AEnemyBase();
	
	virtual void Tick(float DeltaSeconds) override;

	virtual void BeginPlay() override;
	
	UFUNCTION()
	void SetupSpline(ARoute* Spline);

	UFUNCTION()
	void MoveAcrossSpline(float DeltaSeconds);

	UFUNCTION()
	void Die();
	
	UPROPERTY()
	ARoute* Route;

	UPROPERTY()
	TArray<ATowerController*> TowerControllers;

	UPROPERTY(EditAnywhere, Category = "Stats")
	float Speed;
	UPROPERTY()
	float CurrentDistance;

	UPROPERTY()
	float Health;

	UPROPERTY(EditAnywhere, Category = "Stats")
	float MaxHealth;

	UPROPERTY(EditAnywhere)
	class UWidgetComponent* HealthBarComp;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	class UHealthBarWidget* HealthBarWidget;

	UPROPERTY()
	AMainPlayerController* PC;

	UPROPERTY()
	bool bIsDead = false;
};
