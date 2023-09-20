// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_TowerAttack.h"

#include "EnemyBase.h"
#include "TowerBase.h"
#include "TowerController.h"
#include "TowerProjectile.h"

UBTTask_TowerAttack::UBTTask_TowerAttack()
{
	NodeName = TEXT("Tower Attack");
}

EBTNodeResult::Type UBTTask_TowerAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	
	ATowerBase* Tower = Cast<ATowerController>(OwnerComp.GetAIOwner())->TowerOwner;
	ATowerController* TowerController = Cast<ATowerController>(OwnerComp.GetAIOwner());
	AEnemyBase* CurrentEnemy = nullptr;
	
	for (auto Enemy : TowerController->EnemiesInRange)
	{
		if(Enemy)
		{
			if(!CurrentEnemy) {CurrentEnemy = Enemy;}
			else if(
			FVector::Dist(Enemy->GetActorLocation(), TowerController->K2_GetActorLocation()) <
			FVector::Dist(CurrentEnemy->GetActorLocation(), TowerController->K2_GetActorLocation())
			)
			{
				CurrentEnemy = Enemy;
			}
		}
	}
	
	if(Tower && CurrentEnemy && Tower->ProjectileClass)
	{
		// Here we deal damage
		ATowerProjectile* Projectile = GetWorld()->SpawnActor<ATowerProjectile>(Tower->ProjectileClass, Tower->GetActorLocation(), Tower->GetActorRotation());

		Projectile->Direction = (CurrentEnemy->GetActorLocation() - Tower->GetActorLocation()).GetSafeNormal();
		Projectile->TotalDistance =  FVector::Distance(CurrentEnemy->GetActorLocation(), Tower->GetActorLocation());
		Projectile->StartingLocation = Tower->GetActorLocation();

		Projectile->TargetedEnemy = CurrentEnemy;
		
		return EBTNodeResult::Succeeded;	
	}
	return  EBTNodeResult::Failed;
}
