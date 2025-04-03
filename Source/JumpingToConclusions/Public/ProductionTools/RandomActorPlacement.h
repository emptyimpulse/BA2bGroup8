// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "RandomActorPlacement.generated.h"

UCLASS()
class JUMPINGTOCONCLUSIONS_API ARandomActorPlacement : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARandomActorPlacement();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UStaticMeshComponent* StaticMesh;
	FBox Box;

	UFUNCTION(CallInEditor, Category="RandomActorPlacement")
	void RandomiseActor();

	UPROPERTY(EditAnywhere, Category="RandomProperties")
	bool bRandomRotation;
	UPROPERTY(EditAnywhere, Category="RandomProperties")
	bool bRandomLocation;
	UPROPERTY(EditAnywhere, Category="RandomProperties")
	bool bRandomScale;

	UPROPERTY(EditAnywhere, Category="RandomProperties")
	int8 MeshChoice;

	UPROPERTY(EditDefaultsOnly, Category="RandomProperties")
	TArray<UStaticMesh*> StaticMeshOptions;

	FVector SpawnBounds;
};
