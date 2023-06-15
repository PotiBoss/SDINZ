// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Route.generated.h"

class AEnemyBase;
class USplineComponent;

UCLASS()
class SDINZ_API ARoute : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARoute();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	USplineComponent* SplineComponent;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
