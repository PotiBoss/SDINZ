// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayer.h"

#include "MainPlayerController.h"
#include "TowerBase.h"
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
	bShouldCameraMove = true;
	bWhichWay = true;

	if(DetailsWidgetClass)
	{
		DetailsWidget = CreateWidget<UTowerDetailsWidget>(GetLocalViewingPlayerController(), DetailsWidgetClass);
		DetailsWidget->AddToViewport();

		if(PC)
		{
			if(!PC->CurrentTower.TextureUI){return;}
			
			DetailsWidget->TowerSplash->SetBrushFromTexture(PC->CurrentTower.DetailsSplash);
			DetailsWidget->TowerClass->SetBrushFromTexture(PC->CurrentTower.TextureUI);
			DetailsWidget->TowerNameText->SetText(PC->CurrentTower.TowerName);
			DetailsWidget->TowerHealthText->SetText(FText::AsNumber(PC->CurrentTower.Health));
			DetailsWidget->TowerAttackText->SetText(FText::AsNumber(PC->CurrentTower.Damage));
			DetailsWidget->TowerRangeText->SetText(FText::AsNumber(PC->CurrentTower.Range));

			GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Orange, FString::Printf(TEXT("%d"), PC->CurrentTower.Damage));
		}
	}
}

void AMainPlayer::SetCameraGameplay()
{
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
			if(CameraComponent->OrthoWidth >= 3072.0f)
			{
				bShouldCameraMove = false;
				CameraComponent->OrthoWidth = 3072.0f;
			}
		}
		else
		{
			CameraComponent->OrthoWidth -= Speed * DeltaTime;
			if(CameraComponent->OrthoWidth <= 2048.0f)
			{
				bShouldCameraMove = false;
				CameraComponent->OrthoWidth = 2048.0f;
			}
		}
	}
}
