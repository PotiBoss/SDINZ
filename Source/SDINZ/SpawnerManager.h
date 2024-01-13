// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "SpawnerManager.generated.h"

USTRUCT(BlueprintType)
struct FEnemyWave
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<class AEnemyBase> EnemyClass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<class AEnemySpawner*> Spawners;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int RouteIndex;
	
//	UPROPERTY(BlueprintReadWrite, EditAnywhere)
//	int NumberOfEnemies;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int DelayBetweenNextWave;
};

UCLASS()
class SDINZ_API ASpawnerManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnerManager();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FEnemyWave> EnemiesConfig;

	UPROPERTY()
	int WaveIndex;
	UPROPERTY()
	FTimerHandle SpawnHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* MeshComponent;

	UFUNCTION()
	void SpawnNextWave();

	UPROPERTY(EditAnywhere)
	int BaseHealth;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
