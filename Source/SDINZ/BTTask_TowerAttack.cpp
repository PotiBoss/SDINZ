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
	AEnemyBase* Target = Cast<ATowerController>(OwnerComp.GetAIOwner())->CurrentTarget;
	
	if(Tower && Target && Tower->ProjectileClass)
	{
		// Here we deal damage
		ATowerProjectile* Projectile = GetWorld()->SpawnActor<ATowerProjectile>(Tower->ProjectileClass, Tower->GetActorLocation(), Tower->GetActorRotation());

		Projectile->Direction = (Target->GetActorLocation() - Tower->GetActorLocation()).GetSafeNormal();
		Projectile->TotalDistance =  FVector::Distance(Target->GetActorLocation(), Tower->GetActorLocation());
		Projectile->StartingLocation = Tower->GetActorLocation();
		
		return EBTNodeResult::Succeeded;	
	}

	
	return  EBTNodeResult::Failed;
}
