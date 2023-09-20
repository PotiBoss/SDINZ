// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_EnemyInRangeSelector.generated.h"

/**
 * 
 */
UCLASS()
class SDINZ_API UBTService_EnemyInRangeSelector : public UBTService_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTService_EnemyInRangeSelector();
	
	virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
