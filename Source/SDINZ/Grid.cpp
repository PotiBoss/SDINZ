// Fill out your copyright notice in the Description page of Project Settings.


#include "Grid.h"

// Sets default values
AGrid::AGrid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProceduralMeshComponent = CreateDefaultSubobject<UProceduralMeshComponent>("ProceduralMesh");

}

// Called when the game starts or when spawned
void AGrid::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGrid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGrid::SpawnNewGrid()
{
	UMaterialInstanceDynamic* LinesMaterialInstance = CreateMaterialInstance(LineColor, LineOpacity);
	UMaterialInstanceDynamic* SelectionMaterialInstance = CreateMaterialInstance(SelectionColor, SelectionOpacity);

	
	TArray<FVector> LineVertices;
	TArray<int32> LineTriangles;

	// Create horizontal lines geometry
	for(int i = 0; i <= NumRows; i++)
	{
		float LineStart = i * TileSize;
		float LineEnd = GetGridWidth();
		CreateLine(FVector(LineStart, 0, 0), FVector(LineStart, LineEnd, 0), LineThickness, LineVertices, LineTriangles);
	}

	// Create vertical lines geometry
	for(int j = 0; j <= NumColumns; j++)
	{
		float LineStart = j * TileSize;
		float LineEnd = GetGridHeight();
		CreateLine(FVector(0, LineStart, 0), FVector(LineEnd, LineStart, 0), LineThickness, LineVertices, LineTriangles);
	}

	TArray<FVector> Normals; // Default normals, you can leave them empty
	TArray<FVector2D> UV0; // Default UVs, you can leave them empty
	TArray<FLinearColor> VertexColors; // Default vertex colors, you can leave them empty
	TArray<FProcMeshTangent> Tangents;
	
	ProceduralMeshComponent->CreateMeshSection_LinearColor(0, LineVertices, LineTriangles, Normals, UV0, VertexColors, Tangents, true);
}

void AGrid::LocationToTile(FVector Location, bool& bIsValid, int& Row, int& Column)
{
}

void AGrid::TileToGridLocation(int Row, int Column, int bCenter, bool& bIsValid, FVector2D& GridLocation)
{
}

void AGrid::SetSelectedTile(int Row, int Column)
{
}

void AGrid::CreateLine(FVector Start, FVector End, float Thickness, TArray<FVector>& Vertices, TArray<int32>& Triangles)
{
	float HalfThickness = Thickness / 2;

	// Subtract VectorB from VectorA
	FVector SubtractedVector = End - Start;

	// Normalize the subtracted vector
	SubtractedVector.Normalize();

	// Calculate the cross product of VectorA and VectorB after subtraction and normalization
	FVector ThicknessDirection  = FVector::CrossProduct(SubtractedVector, FVector(0, 0, 1.0f));

	int VerticesLength = Vertices.Num();
 
	Triangles.Add(VerticesLength + 2);
	Triangles.Add(VerticesLength + 1);
	Triangles.Add(VerticesLength + 0);

	Triangles.Add(VerticesLength + 2);
	Triangles.Add(VerticesLength + 3);
	Triangles.Add(VerticesLength + 1);
	
	Vertices.Add(FVector(Start + ThicknessDirection * HalfThickness));
	Vertices.Add(FVector(End + ThicknessDirection * HalfThickness));
	Vertices.Add(FVector(Start - ThicknessDirection * HalfThickness));
	Vertices.Add(FVector(End - ThicknessDirection * HalfThickness));

}

float AGrid::GetGridWidth()
{
	return NumColumns * TileSize;
}

float AGrid::GetGridHeight()
{
	return NumRows * TileSize;
}

UMaterialInstanceDynamic* AGrid::CreateMaterialInstance(FLinearColor Color, float Opacity)
{
	UMaterialInstanceDynamic* TempMaterial = UMaterialInstanceDynamic::Create(MaterialBase, this);

	TempMaterial->SetVectorParameterValue("Color", Color);
	TempMaterial->SetScalarParameterValue("Opacity", Opacity);
	
	return TempMaterial;
}
	
bool AGrid::IsTileValid(int Row, int Column)
{
	return true;
}


