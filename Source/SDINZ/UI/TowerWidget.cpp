// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerWidget.h"

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
}

void UTowerWidget::SetVars(UTowerData* Tower)
{
	TowerPropertiesWidget = Tower;
	CostText->SetText(FText::AsNumber(TowerPropertiesWidget->TowerProperties.Cost));
	ClassImage->SetBrushFromTexture(Tower->TowerProperties.TextureUI);
}
