// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerController.h"

#include "TileBase.h"
#include "Kismet/GameplayStatics.h"
#include "Grid.h"
#include "TowerBase.h"

void AMainPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	if(Grid)
	{
		FHitResult HitResult;
		
		if(GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, HitResult))
		{
			bool bIsValid;
			int Row;
			int Column;
		
			Grid->LocationToTile(HitResult.Location, bIsValid, Row, Column);
		
			Grid->SetSelectedTile(Row, Column);
		}
		else
		{
			Grid->SetSelectedTile(-1, -1);
		}
	}

}

void AMainPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("MouseClick", IE_Pressed, this, &AMainPlayerController::OnMousePress);
	InputComponent->BindAction("MouseClick", IE_Released, this, &AMainPlayerController::OnMouseRelease);

	SetShowMouseCursor(true);
}

void AMainPlayerController::BeginPlay()
{
	Super::BeginPlay();

	Grid = Cast<AGrid>(UGameplayStatics::GetActorOfClass(GetWorld(), AGrid::StaticClass()));
	bEnableMouseOverEvents = true;
}

void AMainPlayerController::OnMousePress()
{
	FHitResult HitResult;
	GetHitResultUnderCursor(ECollisionChannel::ECC_Camera, false, HitResult);

	ATileBase* Tile = Cast<ATileBase>(HitResult.GetActor());

	if(Tile)
	{
		Tile->TileClicked();
	}

	if(Grid->GetSelectionGridMeshComponent()->IsVisible())
	{

		bool bIsValid;
		int Row;
		int Column;
		
		Grid->LocationToTile(HitResult.Location, bIsValid, Row, Column);
		
		if(bIsValid)
		{
			bool bIsValid2;
			FVector2D Location2D;
			Grid->TileToGridLocation(Row, Column, true, bIsValid2, Location2D);

			FActorSpawnParameters SpawnParameters;
			GetWorld()->SpawnActor<ATowerBase>(TowerClass, FVector(Location2D.X - 50, Location2D.Y, 50),
				FRotator(0,270,30), SpawnParameters);
		}
	}
}

void AMainPlayerController::OnMouseRelease()
{
}
