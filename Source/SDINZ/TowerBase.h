// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "TileBase.h"
#include "TowerBase.generated.h"

class ATowerProjectile;
enum ETowerType;

USTRUCT(BlueprintType)
struct FTowerProperties
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TEnumAsByte<ETowerType> TowerType = ETowerType::None;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 Cost;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UTexture2D* TextureUI;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<ATowerBase> TowerClass;
};

UCLASS()
class SDINZ_API ATowerBase : public APaperCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATowerBase();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<ATowerProjectile> ProjectileClass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FTowerProperties TowerProperties;

/*	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TEnumAsByte<ETowerType> TowerType = ETowerType::None;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 Cost;
	*/
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
