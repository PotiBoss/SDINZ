// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyGoal.h"

#include "EnemyBase.h"
#include "MainPlayerController.h"
#include "Components/BoxComponent.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "UI/MainGameUI.h"

// Sets default values
AEnemyGoal::AEnemyGoal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	TriggerVolume = CreateDefaultSubobject<UBoxComponent>("TriggerBox");
	SetRootComponent(TriggerVolume);

	TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &AEnemyGoal::OnOverlap);
}

// Called when the game starts or when spawned
void AEnemyGoal::BeginPlay()
{
	Super::BeginPlay();

	PC = Cast<AMainPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
}

void AEnemyGoal::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AEnemyBase* Enemy = Cast<AEnemyBase>(OtherActor);
	if(Enemy)	
	{

		Enemy->Die();

		PC->BaseHealth--;
		PC->MainUI->HealthText->SetText(FText::AsNumber(PC->BaseHealth));
		PC->MainUI->HealthText->SetText(FText::AsNumber(PC->BaseHealth));
	}
}

// Called every frame
void AEnemyGoal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

