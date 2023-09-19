// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TowerProjectile.generated.h"

class USphereComponent;
class UNiagaraComponent;

UCLASS()
class SDINZ_API ATowerProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATowerProjectile();

	UFUNCTION(BlueprintCallable)
	virtual void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep,const FHitResult& SweepResult);

	UPROPERTY()
	FVector TargetLocation;
	UPROPERTY()
	FVector StartingLocation;
	UPROPERTY()
	FVector Direction;

	UPROPERTY()
	float TotalDistance = 0.f;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Speed = 250.0f;

	UPROPERTY()
	float Damage = 5.0f;

	UPROPERTY()
	class AEnemyBase* TargetedEnemy;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USphereComponent* SphereComponent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UNiagaraComponent* NiagaraComponent;

	virtual void Tick(float DeltaSeconds) override;

};
