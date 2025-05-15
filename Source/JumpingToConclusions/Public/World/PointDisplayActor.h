// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TextRenderComponent.h"
#include "GameFramework/Actor.h"
#include "PointDisplayActor.generated.h"

UCLASS()
class JUMPINGTOCONCLUSIONS_API APointDisplayActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APointDisplayActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere)
	UTextRenderComponent* TraitorPoints;
	UPROPERTY(EditAnywhere)
	UTextRenderComponent* SolverPoints;

	void UpdateScoreOnDisplay();

};
