// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerController.h"

#include "TileBase.h"
#include "Kismet/GameplayStatics.h"
#include "Grid.h"
#include "MainPlayer.h"
#include "MyGameInstance.h"
#include "TowerBase.h"
#include "TowerController.h"
#include "TowerData.h"
#include "Blueprint/UserWidget.h"
#include "Components/HorizontalBox.h"
#include "Components/Image.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Perception/AISense_Sight.h"
#include "UI/MainGameUI.h"
#include "UI/TowerDetailsWidget.h"
#include "UI/TowerWidget.h"


void AMainPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	Energy += EnergyGain * DeltaTime;
	MainUI->EnergyBar->SetPercent(Energy - FMath::FloorToInt(Energy));


	if(!TowerWidgets.IsEmpty())
	{
		for(auto TowerWidget : TowerWidgets)
		{
			if(!TowerWidget->TowerPropertiesWidget) {continue;}
			if(TowerWidget->TowerPropertiesWidget->TowerProperties.Cost > Energy)
			{
				TowerWidget->CanvasPanel->SetRenderOpacity(0.3f);
			}
			else
			{
				TowerWidget->CanvasPanel->SetRenderOpacity(1.f);
			}
		}
	}
	
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

	AvailableTowers = Cast<UMyGameInstance>(GetWorld()->GetGameInstance())->ChosenTowers;

	if(MainUIClass)
	{
		MainUI = CreateWidget<UMainGameUI>(this, MainUIClass);
		MainUI->AddToViewport();
		for (auto Tower : AvailableTowers)
		{
			UTowerWidget* TowerWidget = CreateWidget<UTowerWidget>(this, TowerWidgetClass);
			TowerWidget->SetVars(Tower);
			MainUI->TowerHorizontalBox->AddChildToHorizontalBox(TowerWidget);

			TowerWidgets.Add(TowerWidget);
		}
		OnLevelStart();
	}
}

void AMainPlayerController::OnMousePress()
{
	if(MainPlayer->DetailsWidget)
	{
		MainPlayer->SetCameraGameplay();
		FlushPersistentDebugLines(GetWorld());
	}
	
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
			if(Tile->GetTower())
			{
				SelectedTower = Tile->GetTower()->TowerProperties;
				MainPlayer->SetCameraUI();
				
				FColor Color = FColor::Orange;
				DrawDebugCircle(GetWorld(), Tile->GetTower()->GetActorLocation(),
					Tile->GetTower()->TowerProperties->TowerProperties.Range, 120, Color,
					true, -1.f, 0, 5.0f, FVector(0.f, 1.f, 0.f),
					FVector(1.f, 0.f, 0.f), false);
				return;
			}
			
			if(!CurrentTower) { return; }
			
			bool bIsValid2;
			FVector2D Location2D;
			Grid->TileToGridLocation(Row, Column, true, bIsValid2, Location2D);

			FActorSpawnParameters SpawnParameters;
			ATowerBase* SpawnedTower = GetWorld()->SpawnActor<ATowerBase>(CurrentTower->TowerProperties.TowerClass, FVector(Location2D.X - 30, Location2D.Y, 80),
				FRotator(0,270,30), SpawnParameters);
			SpawnedTower->TowerProperties = CurrentTower;

			if(SpawnedTower->TowerProperties->TowerProperties.TowerType != Tile->TileType && Tile->TileType != ETowerType::Both)
			{
				SpawnedTower->Destroy();
				return;
			}
			if(PreviewTower)
			{
				PreviewTower->Destroy();
				PreviewTower = nullptr;

				TArray<AActor*> Tiles;
				UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATileBase::StaticClass(),Tiles);
	
				for (auto TileActor : Tiles)
				{
					ATileBase* TileBase = Cast<ATileBase>(TileActor);
					TileBase->HighlightComponent->SetVisibility(false);
				}
			}

			MainPlayer->SetCameraGameplay();
			
			CurrentTower = nullptr;
			Tile->SetTower(SpawnedTower);
			Energy -= SpawnedTower->TowerProperties->TowerProperties.Cost;

			
		}
	}
}

void AMainPlayerController::OnMouseRelease()
{
}

void AMainPlayerController::OnLevelStart()
{
	SpawnerManager = Cast<ASpawnerManager>(UGameplayStatics::GetActorOfClass(GetWorld(), ASpawnerManager::StaticClass()));

	if(SpawnerManager)
	{
		EnemiesNum = 0;
		for (auto Wave : SpawnerManager->EnemiesConfig)
		{
			EnemiesNum += Wave.Spawners.Num();
		}
		BaseHealth = SpawnerManager->BaseHealth;

		MainUI->HealthText->SetText(FText::AsNumber(BaseHealth));
		MainUI->EnemiesText->SetText(FText::AsNumber(EnemiesNum));
	}
}

void AMainPlayerController::CheckLoseCondition()
{
	if(BaseHealth <= 0)
	{
		CreateWidget(this, GameOverWidgetClass)->AddToViewport();
		UGameplayStatics::SetGamePaused(GetWorld(), true);
	}

	if(EnemiesNum <= 0)
	{
		CreateWidget(this, GameWonWidgetClass)->AddToViewport();
		UGameplayStatics::SetGamePaused(GetWorld(), true);
	}
}
