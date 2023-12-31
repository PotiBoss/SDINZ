// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TileBase.generated.h"

class ATowerBase;

UENUM()
enum ETowerType
{
	None UMETA(DisplayName = "None"),
	Melee UMETA(DisplayName = "Melee"),
	Ranged UMETA(DisplayName = "Ranged"),
	Both UMETA(DisplayName = "Both"),
};

UCLASS()
class SDINZ_API ATileBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATileBase();

	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void TileClicked();

	ATowerBase* GetTower() const;
	void SetTower(ATowerBase* Tower);

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TEnumAsByte<ETowerType> TileType = None;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(VisibleInstanceOnly, Category = "Tower")
	ATowerBase* Tower;

};
