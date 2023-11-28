// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerWidget.h"

#include "Kismet/GameplayStatics.h"
#include "SDINZ/MainPlayer.h"
#include "SDINZ/MainPlayerController.h"

void UTowerWidget::CreateTower()
{
	AMainPlayerController* PC = Cast<AMainPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if(!PC) {return;}
	if(PC->PreviewTower)
	{
		PC->PreviewTower->Destroy();
		PC->PreviewTower = nullptr;
	}

	PC->CurrentTower = TowerPropertiesWidget;
	PC->MainPlayer->SetCameraUI();

	//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Orange, FString::Printf(TEXT("%d"), PC->CurrentTower.Damage));
	//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, FString::Printf(TEXT("%d"), TowerPropertiesWidget.Damage));
	
	FActorSpawnParameters SpawnParameters;
	ATowerBase* SpawnedTower = GetWorld()->SpawnActor<ATowerBase>(TowerPropertiesWidget.TowerClass, FVector(0, 0, 0),
		FRotator(0,0,0), SpawnParameters);
	PC->PreviewTower = SpawnedTower;
}
