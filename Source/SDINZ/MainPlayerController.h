// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SDINZ_API AMainPlayerController : public APlayerController
{
	GENERATED_BODY()

	
protected:
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;

	UFUNCTION()
	void OnMousePress();

	UFUNCTION()
	void OnMouseRelease();
	
	
};
