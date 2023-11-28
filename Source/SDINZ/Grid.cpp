// Fill out your copyright notice in the Description page of Project Settings.


#include "Grid.h"

#include "MainPlayerController.h"
#include "TowerData.h"

// Sets default values
AGrid::AGrid()
{

	ProceduralMeshComponent = CreateDefaultSubobject<UProceduralMeshComponent>("ProceduralMesh");

	ProceduralSelectionMeshComponent = CreateDefaultSubobject<UProceduralMeshComponent>("SelectionProceduralMesh");

}

// Called when the game starts or when spawned
void AGrid::BeginPlay()
{
	Super::BeginPlay();

	PC = Cast<AMainPlayerController>(GetWorld()->GetFirstPlayerController());
}

void AGrid::SpawnNewGrid()
{
	UMaterialInstanceDynamic* LinesMaterialInstance = CreateMaterialInstance(LineColor, LineOpacity);
	UMaterialInstanceDynamic* SelectionMaterialInstance = CreateMaterialInstance(SelectionColorNothing, SelectionOpacity);

	
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

	TArray<FVector> Normals;
	TArray<FVector2D> UV0;
	TArray<FLinearColor> VertexColors; 
	TArray<FProcMeshTangent> Tangents;
	
	ProceduralMeshComponent->CreateMeshSection_LinearColor(0, LineVertices, LineTriangles, Normals, UV0, VertexColors, Tangents, false);
	ProceduralMeshComponent->SetMaterial(0, LinesMaterialInstance);


	TArray<FVector> SelectionVertices;
	TArray<int32> SelectionTriangles;
	
	CreateLine(FVector(0, TileSize / 2, 0), FVector(TileSize, TileSize / 2, 0), TileSize, SelectionVertices, SelectionTriangles);

	ProceduralSelectionMeshComponent->CreateMeshSection_LinearColor(0, SelectionVertices, SelectionTriangles, Normals, UV0, VertexColors, Tangents, false);
	ProceduralSelectionMeshComponent->SetMaterial(0, SelectionMaterialInstance);

	ProceduralSelectionMeshComponent->SetVisibility(false);
}

void AGrid::LocationToTile(FVector Location, bool& bIsValid, int& Row, int& Column)
{
	Row = FMath::Floor((Location.X - GetActorLocation().X) / GetGridHeight() * NumRows);
	Column= FMath::Floor((Location.Y - GetActorLocation().Y) / GetGridWidth() * NumColumns);
	
	bIsValid = IsTileValid(Row, Column);
}

void AGrid::TileToGridLocation(int Row, int Column, bool bCenter, bool& bIsValid, FVector2D& GridLocation)
{
	bIsValid = IsTileValid(Row, Column);

	GridLocation.X = Row * TileSize + GetActorLocation().X;
	GridLocation.Y = Column * TileSize + GetActorLocation().Y;

	if(bCenter)
	{
		GridLocation.X += TileSize / 2;
		GridLocation.Y += TileSize / 2;
	}
}

void AGrid::SetSelectedTile(int Row, int Column)
{
	bool bIsValid;
	FVector2D GridLocation;
	
	TileToGridLocation(Row, Column, false, bIsValid, GridLocation);

	if(bIsValid)
	{
		ProceduralSelectionMeshComponent->SetVisibility(true);
		ProceduralSelectionMeshComponent->SetWorldLocation(FVector(GridLocation.X, GridLocation.Y, GetActorLocation().Z));	
		if(PC->CurrentTower) // ->TowerProperties.TowerClass
		{
			FHitResult HitResult;
			PC->GetHitResultUnderCursor(ECollisionChannel::ECC_Camera, false, HitResult);

			ATileBase* Tile = Cast<ATileBase>(HitResult.GetActor());

			if(PC->PreviewTower)
			{
				PC->PreviewTower->SetActorLocationAndRotation(FVector(GridLocation.X + 20, GridLocation.Y + 50, 80), FRotator(0,270,30));
			}
			
			if(Tile && PC->CurrentTower->TowerProperties.TowerType == Tile->TileType)
			{
				UMaterialInstanceDynamic* SelectionMaterialInstance = CreateMaterialInstance(SelectionColorValid, SelectionOpacity);
				ProceduralSelectionMeshComponent->SetMaterial(0, SelectionMaterialInstance);
			}
			else
			{
				UMaterialInstanceDynamic* SelectionMaterialInstance = CreateMaterialInstance(SelectionColorInValid, SelectionOpacity);
				ProceduralSelectionMeshComponent->SetMaterial(0, SelectionMaterialInstance);
			}
		}
		else
		{
			UMaterialInstanceDynamic* SelectionMaterialInstance = CreateMaterialInstance(SelectionColorNothing, SelectionOpacity);
			ProceduralSelectionMeshComponent->SetMaterial(0, SelectionMaterialInstance);
		}
	}
	else
	{
		ProceduralSelectionMeshComponent->SetVisibility(false);
	}

	PC->CurrentTileLocation = ProceduralSelectionMeshComponent->GetComponentLocation();
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
	if(Row >= 0 && Column >= 0 && Row < NumRows && Column < NumColumns) return true;
	return false;
}


