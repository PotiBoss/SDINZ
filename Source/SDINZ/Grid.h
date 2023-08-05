// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProceduralMeshComponent.h"
#include "GameFramework/Actor.h"
#include "Grid.generated.h"

UCLASS()
class SDINZ_API AGrid : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGrid();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void LocationToTile(FVector Location,  bool& bIsValid,  int& Row,  int& Column);

	UFUNCTION()
	void TileToGridLocation(int Row, int Column, int bCenter,  bool& bIsValid,  FVector2D& GridLocation);

	UFUNCTION()
	void SetSelectedTile(int Row, int Column);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UFUNCTION(CallInEditor, BlueprintCallable)
	void SpawnNewGrid();
	
	UFUNCTION()
	void CreateLine(FVector Start, FVector End, float Thickness, TArray<FVector>& Vertices, TArray<int>& Triangles);

	UFUNCTION()
	float GetGridWidth();

	UFUNCTION()
	float GetGridHeight();

	UFUNCTION()
	UMaterialInstanceDynamic* CreateMaterialInstance(FLinearColor Color, float Opacity);

	UFUNCTION()
	bool IsTileValid(int Row, int Column);

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UProceduralMeshComponent* ProceduralMeshComponent;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UMaterialInstance* MaterialBase;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Constants")
	int NumRows;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Constants")
	int NumColumns;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Constants")
	float TileSize;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Constants")
	float LineThickness;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Constants")
	FLinearColor LineColor;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Constants")
	FLinearColor SelectionColor;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Constants")
	float LineOpacity;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Constants")
	float SelectionOpacity;
};
