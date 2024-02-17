// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerWidget.h"

#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "SDINZ/MainPlayer.h"
#include "SDINZ/MainPlayerController.h"
#include "SDINZ/TowerData.h"

void UTowerWidget::CreateTower()
{
	AMainPlayerController* PC = Cast<AMainPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if(!PC) {return;}
	if(TowerPropertiesWidget->TowerProperties.Cost > PC->Energy){return;}
	if(PC->PreviewTower)
	{
		PC->PreviewTower->Destroy();
		PC->PreviewTower = nullptr;
	}

	PC->CurrentTower = TowerPropertiesWidget;
	PC->MainPlayer->SetCameraUI();
	
	FActorSpawnParameters SpawnParameters;
	ATowerBase* SpawnedTower = GetWorld()->SpawnActor<ATowerBase>(TowerPropertiesWidget->TowerProperties.TowerClass, FVector(0, 0, 0),
		FRotator(0,0,0), SpawnParameters);
	PC->PreviewTower = SpawnedTower;

	TArray<AActor*> Tiles;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATileBase::StaticClass(),Tiles);
	
	for (auto TileActor : Tiles)
	{
		ATileBase* Tile = Cast<ATileBase>(TileActor);
		Tile->HighlightComponent->SetVisibility(true);

		Tile->TileType == ETowerType::Both || Tile->TileType == PC->CurrentTower->TowerProperties.TowerType && !Tile->GetTower()
		? Tile->HighlightComponent->SetMaterial(0, Tile->MaterialInterfaceGreen)
		: Tile->HighlightComponent->SetVisibility(false);
	}
	
}

void UTowerWidget::SetVars(UTowerData* Tower)
{
	if(!Tower)
	{
		CostText->SetVisibility(ESlateVisibility::Collapsed);
		ClassImage->SetVisibility(ESlateVisibility::Collapsed);
		ClassButton->SetVisibility(ESlateVisibility::Collapsed);
		TowerPropertiesWidget = nullptr;
		return;
	}
	CostText->SetVisibility(ESlateVisibility::Visible);
	ClassImage->SetVisibility(ESlateVisibility::Visible);
	ClassButton->SetVisibility(ESlateVisibility::Visible);
	
	TowerPropertiesWidget = Tower;
	CostText->SetText(FText::AsNumber(TowerPropertiesWidget->TowerProperties.Cost));
	ClassImage->SetBrushFromTexture(Tower->TowerProperties.TextureUI);
	
	FSlateBrush ImageBrush;
	ImageBrush.SetResourceObject(TowerPropertiesWidget->TowerProperties.DetailsSplash);

	FButtonStyle ButtonStyle;
	ButtonStyle.Normal = ImageBrush;
	ButtonStyle.Normal.TintColor = FSlateColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));
	ButtonStyle.Hovered = ImageBrush;
	ButtonStyle.Hovered.TintColor = FSlateColor(FLinearColor(1.0f, 1.0f, 1.0f, 0.4f));
	ButtonStyle.Pressed = ImageBrush;
	ButtonStyle.Pressed.TintColor = FSlateColor(FLinearColor(1.0f, 1.0f, 1.0f, 0.2f));
	
	ClassButton->SetStyle(ButtonStyle);
}
