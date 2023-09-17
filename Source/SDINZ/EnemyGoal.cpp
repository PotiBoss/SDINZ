// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyGoal.h"

#include "EnemyBase.h"

// Sets default values
AEnemyGoal::AEnemyGoal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemyGoal::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemyGoal::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AEnemyBase* Enemy = Cast<AEnemyBase>(OtherActor);
	if(Enemy)	
	{
		Enemy->Destroy();
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Orange, TEXT("EnemyGoal cpp enemy reached end"));
	}
}

// Called every frame
void AEnemyGoal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

