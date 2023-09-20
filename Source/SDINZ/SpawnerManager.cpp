// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnerManager.h"

#include "EnemySpawner.h"

// Sets default values
ASpawnerManager::ASpawnerManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(MeshComponent);

	WaveIndex = 0;

}

void ASpawnerManager::SpawnNextWave()
{
	GEngine->AddOnScreenDebugMessage(-1,3.0f, FColor::Orange, TEXT("Wave"));
	
	for (auto Spawner : EnemiesConfig[WaveIndex].Spawners)
	{
		Spawner->SpawnEnemy(EnemiesConfig[WaveIndex].EnemyClass, EnemiesConfig[WaveIndex].RouteIndex);
	}
	
	if(++WaveIndex < EnemiesConfig.Num())
	{
		GEngine->AddOnScreenDebugMessage(-1,3.0f, FColor::Orange, TEXT("NextWave"));
		GetWorldTimerManager().SetTimer(
			SpawnHandle, this, &ASpawnerManager::SpawnNextWave, EnemiesConfig[WaveIndex - 1].DelayBetweenNextWave, false);		
	}
}

// Called when the game starts or when spawned
void ASpawnerManager::BeginPlay()
{
	Super::BeginPlay();
	
	if(!EnemiesConfig.IsEmpty())
	{
		GetWorldTimerManager().SetTimer(
		SpawnHandle, this, &ASpawnerManager::SpawnNextWave, 3.0f, false);	
	}
}

// Called every frame
void ASpawnerManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

