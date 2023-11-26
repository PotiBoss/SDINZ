// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayer.h"

#include "Blueprint/UserWidget.h"
#include "Camera/CameraComponent.h"
#include "Components/SplineComponent.h"
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
