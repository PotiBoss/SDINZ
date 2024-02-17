// Fill out your copyright notice in the Description page of Project Settings.


#include "TileBase.h"

// Sets default values
ATileBase::ATileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("MeshComponent");
	SetRootComponent(MeshComponent);
	HighlightComponent = CreateDefaultSubobject<UStaticMeshComponent>("HighlightComponent");
	HighlightComponent->SetupAttachment(MeshComponent);
}

// Called when the game starts or when spawned
void ATileBase::BeginPlay()
{
	Super::BeginPlay();
	
}

ATowerBase* ATileBase::GetTower() const
{
	return Tower;
}

void ATileBase::SetTower(ATowerBase* InTower)
{
	Tower = InTower;
}

void ATileBase::TileClicked()
{
	//GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Orange, FString::Printf(TEXT("Clicked tile: %s"), *GetName()));
}

// Called every frame
void ATileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

