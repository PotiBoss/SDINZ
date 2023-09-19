// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawner.h"

#include "Route.h"
#include "Components/BoxComponent.h"

// Sets default values
AEnemySpawner::AEnemySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TriggerVolume = CreateDefaultSubobject<UBoxComponent>("TriggerBox");
	SetRootComponent(TriggerVolume);
}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(
		SpawnHandle, this, &AEnemySpawner::SpawnEnemy, EnemiesConfig[0].DelayBetweenEnemies, false, 1.0f);
}

void AEnemySpawner::CreateNewRoute()
{
	Routes.Add(GetWorld()->SpawnActor<ARoute>(GetActorLocation(), GetActorRotation()));
}

void AEnemySpawner::SpawnEnemy()
{
	AEnemyBase* EnemySpawned = GetWorld()->SpawnActor<AEnemyBase>(EnemiesConfig[WaveIndex].EnemyClass, GetActorLocation(), GetActorRotation());
	ARoute* Route = Routes[EnemiesConfig[WaveIndex].RouteIndex];
	
	if(Route)
	{
		EnemySpawned->SetupSpline(Route);
	}
	
	// Spawn next wave
	if(--EnemiesConfig[WaveIndex].NumberOfEnemies <= 0)
	{
		WaveIndex++;

		if(WaveIndex <= EnemiesConfig.Num())
		{
			GetWorldTimerManager().SetTimer(
	SpawnHandle, this, &AEnemySpawner::SpawnEnemy,
	EnemiesConfig[WaveIndex - 1].DelayBetweenNextWave, false, EnemiesConfig[WaveIndex - 1].DelayBetweenNextWave);
		}
	}
	else
	{
		GetWorldTimerManager().SetTimer(
	SpawnHandle, this, &AEnemySpawner::SpawnEnemy, EnemiesConfig[WaveIndex].DelayBetweenEnemies, false, EnemiesConfig[WaveIndex].DelayBetweenEnemies);
	}
}

// Called every frame
void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

