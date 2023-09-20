// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerProjectile.h"

#include "EnemyBase.h"
#include "HealthBarWidget.h"
#include "NiagaraComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
ATowerProjectile::ATowerProjectile()
{
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SetRootComponent(SphereComponent);
	
	NiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComponent"));
	NiagaraComponent->SetupAttachment(SphereComponent);
	
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ATowerProjectile::OnOverlap);

	PrimaryActorTick.bCanEverTick = true;
}

void ATowerProjectile::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Orange, TEXT("Trap collision started overlaping c++ without override"));
}

// Called when the game starts or when spawned
void ATowerProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATowerProjectile::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	float CurrentDistance = FVector::Distance(GetActorLocation(), StartingLocation);

	if(TotalDistance >= CurrentDistance)
	{
		FVector CurrentLocation = GetActorLocation();

		CurrentLocation += Direction * Speed * DeltaSeconds;

		SetActorLocation(CurrentLocation);
	}
	else
	{
		if(TargetedEnemy)
		{
			TargetedEnemy->Health -= Damage;
			TargetedEnemy->HealthBarWidget->SetHealthBar(TargetedEnemy->Health / TargetedEnemy->MaxHealth);
			if(TargetedEnemy->Health <= 0)
			{
				TargetedEnemy->Die();
			}
		}
		Destroy();
	}
}

