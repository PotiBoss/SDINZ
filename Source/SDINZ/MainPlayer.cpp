// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayer.h"

#include "MainPlayerController.h"
#include "TowerBase.h"
#include "TowerData.h"
#include "Blueprint/UserWidget.h"
#include "Camera/CameraComponent.h"
#include "Components/Image.h"
#include "Components/SplineComponent.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "UI/TowerDetailsWidget.h"

// Sets default values
AMainPlayer::AMainPlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("SplineComponent"));
}

void AMainPlayer::SetCameraUI()
{
	if(bWhichWay == false)
	{
		const float CurrentTimeDilation = UGameplayStatics::GetGlobalTimeDilation(GetWorld());
		UGameplayStatics::SetGlobalTimeDilation(GetWorld(), CurrentTimeDilation * 0.5);
	}
	
	
	bShouldCameraMove = true;
	bWhichWay = true;

	if(DetailsWidgetClass)
	{
		if(!DetailsWidget)
		{
			DetailsWidget = CreateWidget<UTowerDetailsWidget>(GetLocalViewingPlayerController(), DetailsWidgetClass);
			DetailsWidget->AddToViewport();
		}
		
		if(PC)
		{
			if(PC->CurrentTower)
			{
				DetailsWidget->TowerSplash->SetBrushFromTexture(PC->CurrentTower->TowerProperties.DetailsSplash);
				DetailsWidget->TowerClass->SetBrushFromTexture(PC->CurrentTower->TowerProperties.TextureUI);
				DetailsWidget->TowerNameText->SetText(PC->CurrentTower->TowerProperties.TowerName);
				DetailsWidget->TowerHealthText->SetText(FText::AsNumber(PC->CurrentTower->TowerProperties.Health));
				DetailsWidget->TowerAttackText->SetText(FText::AsNumber(PC->CurrentTower->TowerProperties.Damage));
				DetailsWidget->TowerRangeText->SetText(FText::AsNumber(PC->CurrentTower->TowerProperties.Range));
				DetailsWidget->TowerAttackSpeedText->SetText(FText::AsNumber(PC->CurrentTower->TowerProperties.AttackSpeed));
			}
			else if(PC->SelectedTower)
			{
				DetailsWidget->TowerSplash->SetBrushFromTexture(PC->SelectedTower->TowerProperties.DetailsSplash);
				DetailsWidget->TowerClass->SetBrushFromTexture(PC->SelectedTower->TowerProperties.TextureUI);
				DetailsWidget->TowerNameText->SetText(PC->SelectedTower->TowerProperties.TowerName);
				DetailsWidget->TowerHealthText->SetText(FText::AsNumber(PC->SelectedTower->TowerProperties.Health));
				DetailsWidget->TowerAttackText->SetText(FText::AsNumber(PC->SelectedTower->TowerProperties.Damage));
				DetailsWidget->TowerRangeText->SetText(FText::AsNumber(PC->SelectedTower->TowerProperties.Range));
				DetailsWidget->TowerAttackSpeedText->SetText(FText::AsNumber(PC->SelectedTower->TowerProperties.AttackSpeed));
			}

		}
	}
}

void AMainPlayer::SetCameraGameplay()
{
	if(bWhichWay == true)
	{
		const float CurrentTimeDilation = UGameplayStatics::GetGlobalTimeDilation(GetWorld());
		UGameplayStatics::SetGlobalTimeDilation(GetWorld(), CurrentTimeDilation * 2);
	}
	
	bShouldCameraMove = true;
	bWhichWay = false;
	
	if(DetailsWidget)
	{
		DetailsWidget->RemoveFromParent();
		DetailsWidget->Destruct();
		DetailsWidget = nullptr;
	}
}

// Called when the game starts or when spawned
void AMainPlayer::BeginPlay()
{
	Super::BeginPlay();

	PC = Cast<AMainPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
}

// Called every frame
void AMainPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(bShouldCameraMove)
	{
		if(bWhichWay)
		{
			CameraComponent->OrthoWidth += Speed * DeltaTime;
			if(CameraComponent->OrthoWidth >= 2500.0f)
			{
				bShouldCameraMove = false;
				CameraComponent->OrthoWidth = 2500.0f;
			}
		}
		else
		{
			CameraComponent->OrthoWidth -= Speed * DeltaTime;
			if(CameraComponent->OrthoWidth <= 1900.0f)
			{
				bShouldCameraMove = false;
				CameraComponent->OrthoWidth = 1900.0f;
			}
		}
	}
}
