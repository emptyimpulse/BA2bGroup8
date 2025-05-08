// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "World/InteractableActors.h"
#include "Subsystems/JTCGameState.h"
#include "ObeserverGuessingActor.generated.h"

/**
 * 
 */
UCLASS()
class JUMPINGTOCONCLUSIONS_API AObeserverGuessingActor : public AInteractableActors
{
	GENERATED_BODY()

public:
	AObeserverGuessingActor();

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* SceneAsset;

	UPROPERTY(EditDefaultsOnly)
	UTextRenderComponent* PlayerNameDisplay;

	UPROPERTY(EditAnywhere)
	USphereComponent* InteractDistance;
	
	UPROPERTY(Replicated)
	APlayerState* ChosenPlayerController;
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void SetPlayerChosenIndex();

public:
	virtual void Interact_Implementation(AJumpingToConclusionsCharacter* InstigatingPlayer) override;
};
