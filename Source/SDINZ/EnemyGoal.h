// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainPlayerController.h"
#include "GameFramework/Actor.h"
#include "EnemyGoal.generated.h"

UCLASS()
class SDINZ_API AEnemyGoal : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyGoal();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UBoxComponent* TriggerVolume;

	UFUNCTION(BlueprintCallable)
	virtual void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep,const FHitResult& SweepResult);

	UPROPERTY()
	AMainPlayerController* PC;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
