// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBase.h"

#include "HealthBarWidget.h"
#include "Route.h"
#include "Blueprint/UserWidget.h"
#include "Components/SplineComponent.h"
#include "Components/WidgetComponent.h"


AEnemyBase::AEnemyBase()
{
	Speed = 100.0f; 
	CurrentDistance = 0.0f;
	
	HealthBarComp = CreateDefaultSubobject<UWidgetComponent>("HealthBarComp");
}

void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	HealthBarWidget = Cast<UHealthBarWidget>(HealthBarComp->GetWidget());
	if(HealthBarWidget)
	{
		//HealthBarComp->SetWorldRotation(FRotator(0,0, 90.0f));
		HealthBarWidget->SetHealthBar(100.0f);
	}
}

void AEnemyBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	MoveAcrossSpline(DeltaSeconds);
}

void AEnemyBase::SetupSpline(ARoute* NewRoute)
{
	Route = NewRoute;

	// Set the actor's initial location to the start of the spline
	if (Route)
	{
		SetActorLocation(Route->SplineComponent->GetLocationAtDistanceAlongSpline(CurrentDistance, ESplineCoordinateSpace::World));
	}
}

void AEnemyBase::MoveAcrossSpline(float DeltaSeconds)
{
	if (Route)
	{
		// Increment the current distance based on the speed and delta time
		CurrentDistance += Speed * DeltaSeconds;

		// Wrap the current distance to keep the actor looping along the spline
		if (CurrentDistance >= Route->SplineComponent->GetSplineLength())
		{
			CurrentDistance -= Route->SplineComponent->GetSplineLength();
		}

		// Set the actor's location based on the new distance along the spline
		SetActorLocation(Route->SplineComponent->GetLocationAtDistanceAlongSpline(CurrentDistance, ESplineCoordinateSpace::World));
	}
}
