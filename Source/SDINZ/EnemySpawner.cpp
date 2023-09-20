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

	WaveIndex = 0;
}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemySpawner::CreateNewRoute()
{
	Routes.Add(GetWorld()->SpawnActor<ARoute>(GetActorLocation(), GetActorRotation()));
}

void AEnemySpawner::SpawnEnemy(TSubclassOf<AEnemyBase> EnemyClass, int RouteIndex)
{
	AEnemyBase* EnemySpawned = GetWorld()->SpawnActor<AEnemyBase>(EnemyClass, GetActorLocation(), GetActorRotation());
	EnemySpawned->SetupSpline(Routes[RouteIndex]);
	GEngine->AddOnScreenDebugMessage(-1,3.0f, FColor::Orange, TEXT("Spawn guy"));
}

// Called every frame
void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

