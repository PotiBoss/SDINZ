// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "TowerController.generated.h"

class AEnemyBase;
class UBehaviorTreeComponent;
class ATowerBase;

/**
 * 
 */
UCLASS()
class SDINZ_API ATowerController : public AAIController
{
	GENERATED_BODY()
	
public:
	ATowerController();

	void ChooseTarget();
	
	UPROPERTY(BlueprintReadWrite)
	ATowerBase* TowerOwner;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	AEnemyBase* CurrentTarget;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TArray<AEnemyBase*> EnemiesInRange;
	
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	bool bHasTarget = false;;
	
protected:
	UFUNCTION()
	void OnStimulusChange(AActor* UpdatedActor, struct FAIStimulus Stimulus);

	virtual void OnPossess(APawn* InPawn) override;

	
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = true))
	UBehaviorTree* BehaviorTree;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI", meta = (AllowPrivateAccess = true))
	UBehaviorTreeComponent* BehaviorTreeComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI", meta = (AllowPrivateAccess = true))
	UBlackboardComponent* BlackboardComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI", meta = (AllowPrivateAccess = true))
	UAIPerceptionComponent* PerceptionComp;
};
