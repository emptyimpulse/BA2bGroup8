// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PuzzleAnswerCubesTemp.generated.h"

class AJtcPlayerController;
class UPuzzleAnswerSheet;
class USphereComponent;

UCLASS()
class JUMPINGTOCONCLUSIONS_API APuzzleAnswerCubesTemp : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APuzzleAnswerCubesTemp();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	USceneComponent* StaticMesh;

	UPROPERTY(EditAnywhere)
	USphereComponent* OverlapSphere;
	
	UPROPERTY(EditAnywhere)
	int32 AnswerCubeIndex;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UPuzzleAnswerSheet> WidgetReference;

	UPROPERTY()
	UPuzzleAnswerSheet* CreatedWidget;

	UFUNCTION()
	void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent,
					 AActor* OtherActor,
					 UPrimitiveComponent* OtherComp,
					 int32 OtherBodyIndex,
					 bool bFromSweep,
					 const FHitResult& SweepResult);

	UFUNCTION(Client,Reliable)
	void ShowOnPlayerScreen(APlayerController* Player);
};
