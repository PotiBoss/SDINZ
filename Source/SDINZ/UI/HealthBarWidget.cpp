// Fill out your copyright notice in the Description page of Project Settings.


#include <SDINZ/HealthBarWidget.h>

#include "Components/ProgressBar.h"

void UHealthBarWidget::SetHealthBar(float Percentage)
{
	HealthBar->SetPercent(Percentage);
}
