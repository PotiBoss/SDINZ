// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerController.h"

#include "EnemyBase.h"
#include "TowerBase.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"

ATowerController::ATowerController()
{
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("Behavior Tree Component"));
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard Component"));

}

void ATowerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	PerceptionComp = FindComponentByClass<UAIPerceptionComponent>();

	TowerOwner = Cast<ATowerBase>(InPawn);

	if(Blackboard && BehaviorTree)
	{
		Blackboard->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
		RunBehaviorTree(BehaviorTree);
		BehaviorTreeComponent->StartTree(*BehaviorTree);
	}

	if(PerceptionComp)
	{
		PerceptionComp->OnTargetPerceptionUpdated.AddDynamic(this, &ATowerController::OnStimulusChange);
	}
}

void ATowerController::OnStimulusChange(AActor* UpdatedActor, FAIStimulus Stimulus)
{
	AEnemyBase* Enemy = Cast<AEnemyBase>(UpdatedActor);

	if(Stimulus.IsActive())
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Orange, TEXT("Enemy in range"));
		if(Enemy)
		{
			EnemiesInRange.AddUnique(Enemy);
		}
	}
	if(!Stimulus.IsActive())
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Orange, TEXT("Not in range"));
		if(Enemy)
		{
			if(CurrentTarget == Enemy)
			{
				bHasTarget = false;
				CurrentTarget = nullptr;
				GetBlackboardComponent()->SetValueAsObject("Target", nullptr);
			}
			EnemiesInRange.Remove(Enemy);
		}
	}
	for (auto EnemyArr : EnemiesInRange)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Orange, FString::Printf(TEXT("%s"), *EnemyArr->GetName()));
	}

	if(!bHasTarget)
	{
		if(!EnemiesInRange.IsEmpty())
		{
			bHasTarget = true;
			CurrentTarget = EnemiesInRange[0];
			GetBlackboardComponent()->SetValueAsObject("Target", CurrentTarget);
		}
	}
}
