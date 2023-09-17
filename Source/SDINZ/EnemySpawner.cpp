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

	for (auto EnemyClass : Enemies)
	{
		SpawnEnemy(EnemyClass, Routes[0]);
	}
}

void AEnemySpawner::CreateNewRoute()
{
	Routes.Add(GetWorld()->SpawnActor<ARoute>(GetActorLocation(), GetActorRotation()));
}

void AEnemySpawner::SpawnEnemy(TSubclassOf<AEnemyBase> EnemyToSpawn, ARoute* Route)
{
	AEnemyBase* EnemySpawned = GetWorld()->SpawnActor<AEnemyBase>(EnemyToSpawn, GetActorLocation(), GetActorRotation());

	if(Route)
	{
		EnemySpawned->SetupSpline(Route);
	}
}

// Called every frame
void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

