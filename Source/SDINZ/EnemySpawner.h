// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyBase.h"
#include "Engine/SplineMeshActor.h"
#include "GameFramework/Actor.h"
#include "EnemySpawner.generated.h"

class UBoxComponent;
class AEnemyBase;
class ASplineMeshActor;
class ARoute;

UCLASS()
class SDINZ_API AEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemySpawner();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(CallInEditor)
	void CreateNewRoute();

	// Spawns enemy from given class to walk a given route
	void SpawnEnemy(TSubclassOf<AEnemyBase> EnemyToSpawn, ARoute* Route = nullptr);

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UBoxComponent* TriggerVolume;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<ARoute*> Routes;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<TSubclassOf<AEnemyBase>> Enemies;
};
