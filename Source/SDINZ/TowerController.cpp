// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerController.h"

#include "EnemyBase.h"
#include "TowerBase.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig.h"

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
		if(Enemy)
		{
			EnemiesInRange.AddUnique(Enemy);
			Enemy->TowerControllers.Add(this);
		}
	}
	if(!Stimulus.IsActive())
	{
		if(Enemy)
		{
			EnemiesInRange.Remove(Enemy);
			Enemy->TowerControllers.Remove(this);
		}
	}
}
