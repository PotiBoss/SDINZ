// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerController.h"

#include "TileBase.h"

void AMainPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
}

void AMainPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("MouseClick", IE_Pressed, this, &AMainPlayerController::OnMousePress);
	InputComponent->BindAction("MouseClick", IE_Released, this, &AMainPlayerController::OnMouseRelease);

	SetShowMouseCursor(true);
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
	
}

void AMainPlayerController::OnMouseRelease()
{
}
