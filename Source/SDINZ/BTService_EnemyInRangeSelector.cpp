// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_EnemyInRangeSelector.h"

#include "EnemyBase.h"
#include "TowerController.h"

UBTService_EnemyInRangeSelector::UBTService_EnemyInRangeSelector()
{
	NodeName = "Check Enemies in range";

	bNotifyBecomeRelevant = true;

	Interval = 0.5f;
	RandomDeviation = 0.0f;
}

void UBTService_EnemyInRangeSelector::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ATowerController* TowerController = Cast<ATowerController>(OwnerComp.GetAIOwner());

	//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Orange, TEXT("Serwis"));

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
				//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Orange, TEXT("Zmiana goscia"));
			}
		}
	}
}

