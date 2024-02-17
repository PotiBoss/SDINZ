// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpawnerManager.h"
#include "GameFramework/Pawn.h"
#include "MainPlayer.generated.h"

struct FTowerProperties;
class UTowerDetailsWidget;
class AMainPlayerController;

UCLASS()
class SDINZ_API AMainPlayer : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMainPlayer();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USceneComponent* SceneRoot;

	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* CameraComponent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class USplineComponent* SplineComponent;
	
	UPROPERTY(EditAnywhere, Category = "Spline")
	float Speed;
	UPROPERTY()
	bool bShouldCameraMove;
	UPROPERTY()
	bool bWhichWay;
	
	UFUNCTION(BlueprintCallable)
	void SetCameraUI();
	UFUNCTION(BlueprintCallable)
	void SetCameraGameplay();

	UPROPERTY(BlueprintReadWrite)
	UTowerDetailsWidget* DetailsWidget;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> DetailsWidgetClass;

	UPROPERTY()
	AMainPlayerController* PC;
	
	UPROPERTY()
	ASpawnerManager* SpawnerManager;
};
