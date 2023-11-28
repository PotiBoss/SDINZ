// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerController.h"

#include "TileBase.h"
#include "Kismet/GameplayStatics.h"
#include "Grid.h"
#include "MainPlayer.h"
#include "TowerBase.h"
#include "TowerData.h"
#include "Blueprint/UserWidget.h"
#include "Components/HorizontalBox.h"
#include "Components/TextBlock.h"
#include "UI/MainGameUI.h"
#include "UI/TowerWidget.h"

void AMainPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	if(Grid)
	{
		if(Grid->bIsHoveringUI)
		{
			Grid->SetSelectedTile(-1, -1);
			return;
		}
		
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

	/*if(PreviewTower)
	{
		FVector Location;
		FRotator Rotation;
		
		PreviewTower->SetActorLocationAndRotation(Location, Rotation, false);
	}
	*/
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

	MainPlayer = Cast<AMainPlayer>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	if(MainUIClass)
	{
		MainUI = CreateWidget<UMainGameUI>(this, MainUIClass);
		MainUI->AddToViewport();
		for (auto Tower : AvailableTowers)
		{
			UTowerWidget* TowerWidget = CreateWidget<UTowerWidget>(this, TowerWidgetClass);
			TowerWidget->TowerPropertiesWidget = Tower->TowerProperties;
			TowerWidget->CostText->SetText(FText::AsNumber(TowerWidget->TowerPropertiesWidget.Cost));
			MainUI->TowerHorizontalBox->AddChildToHorizontalBox(TowerWidget);

			GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Black, FString::Printf(TEXT("%d"), TowerWidget->TowerPropertiesWidget.Damage));
			GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, FString::Printf(TEXT("%d"), Tower->TowerProperties.Damage));
		}
	}
}

void AMainPlayerController::OnMousePress()
{
	FHitResult HitResult;
	GetHitResultUnderCursor(ECollisionChannel::ECC_Camera, false, HitResult);

	ATileBase* Tile = Cast<ATileBase>(HitResult.GetActor());

	if(!Tile) { return; }
	
	Tile->TileClicked();
	

	if(Grid->GetSelectionGridMeshComponent()->IsVisible())
	{
		
		bool bIsValid;
		int Row;
		int Column;
		
		Grid->LocationToTile(HitResult.Location, bIsValid, Row, Column);
		
		if(bIsValid)
		{
			if(Tile->GetTower()) { return; }
			if(!CurrentTower.TowerClass) { return; }
			
			bool bIsValid2;
			FVector2D Location2D;
			Grid->TileToGridLocation(Row, Column, true, bIsValid2, Location2D);

			FActorSpawnParameters SpawnParameters;
			ATowerBase* SpawnedTower = GetWorld()->SpawnActor<ATowerBase>(CurrentTower.TowerClass, FVector(Location2D.X - 30, Location2D.Y, 80),
				FRotator(0,270,30), SpawnParameters);
			SpawnedTower->TowerProperties = CurrentTower;

			if(SpawnedTower->TowerProperties.TowerType != Tile->TileType && Tile->TileType != ETowerType::Both)
			{
				SpawnedTower->Destroy();
				return;
			}
			if(PreviewTower)
			{
				PreviewTower->Destroy();
				PreviewTower = nullptr;
			}

			MainPlayer->SetCameraGameplay();
			
			CurrentTower.TowerClass = nullptr; //
			Tile->SetTower(SpawnedTower);
		}
	}
}

void AMainPlayerController::OnMouseRelease()
{
}
