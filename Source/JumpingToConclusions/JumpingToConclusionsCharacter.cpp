// Copyright Epic Games, Inc. All Rights Reserved.

#include "JumpingToConclusionsCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "JumpingToConclusionsGameMode.h"
#include "Components/TextRenderComponent.h"
#include "Interfaces/InteractionInterface.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Subsystems/JTCGameState.h"
#include "World/PuzzleAnswerCubesTemp.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// AJumpingToConclusionsCharacter

AJumpingToConclusionsCharacter::AJumpingToConclusionsCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	PlayerName = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Player"));
	PlayerName->SetupAttachment(RootComponent);
	PlayerName->SetText(FText::FromString("Null"));

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	GrabPosisitonComponent = CreateDefaultSubobject<USceneComponent>(TEXT("GrabPosition"));
	GrabPosisitonComponent->SetupAttachment(RootComponent);

	PhysicsHandleComponent = CreateDefaultSubobject<UPhysicsHandleComponent>(TEXT("PhysicsHandleComponent"));

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

void AJumpingToConclusionsCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
}


void AJumpingToConclusionsCharacter::SetName()
{
	PlayerName->SetText(FText::FromString(GetController()->GetName()));
}


//////////////////////////////////////////////////////////////////////////
// Input

void AJumpingToConclusionsCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AJumpingToConclusionsCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AJumpingToConclusionsCharacter::Look);

		EnhancedInputComponent->BindAction(PickupAction, ETriggerEvent::Started, this, &AJumpingToConclusionsCharacter::Pickup);

		EnhancedInputComponent->BindAction(PickupAction, ETriggerEvent::Completed, this, &AJumpingToConclusionsCharacter::Drop);


	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AJumpingToConclusionsCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AJumpingToConclusionsCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}
void AJumpingToConclusionsCharacter::ServerPickTraitor_Implementation(APlayerController* ChosenPlayerController)
{
	AGameModeBase* GM = GetWorld()->GetAuthGameMode();
	if (GM)
	{
		if (AJumpingToConclusionsGameMode* CustomGameMode = Cast<AJumpingToConclusionsGameMode>(GM))
		{
			CustomGameMode->CheckIfTraitorCorrect(ChosenPlayerController);
		}
	}
}
void AJumpingToConclusionsCharacter::Pickup()
{

	//TODO make the pickup items work, its broken rn so im using it to debug other stuff

	TArray<AActor*> OverlappingActors;
	GetOverlappingActors(OverlappingActors);

	for (AActor* OverlappingActor : OverlappingActors)
	{
		if (OverlappingActor->GetClass()->ImplementsInterface(UInteractionInterface::StaticClass()))
		{
			FoundInteractable(OverlappingActor);
		}
	}
}

void AJumpingToConclusionsCharacter::PickupItem_Implementation(AActor* HitActor)
{
	/*UPrimitiveComponent* HitActorRoot = Cast<UPrimitiveComponent>(HitActor->GetRootComponent());
	if (HitActorRoot && HitActorRoot->IsSimulatingPhysics())
	{
		GEngine->AddOnScreenDebugMessage(-1,2.0f, FColor::Red, "Server Is Simulating Physics");

		PhysicsHandleComponent->GrabComponentAtLocation(HitActorRoot,NAME_None,GrabPosisitonComponent->GetComponentLocation());
	}*/
}

void AJumpingToConclusionsCharacter::Drop()
{
	
}

void AJumpingToConclusionsCharacter::DropItem_Implementation()
{
	
}

void AJumpingToConclusionsCharacter::FoundInteractable(AActor* FoundInteractableActor)
{
	AInteractableActors* PuzzleInteractable = Cast<AInteractableActors>(FoundInteractableActor);
	if (PuzzleInteractable)
	{
		GEngine->AddOnScreenDebugMessage(-1,2.0f,FColor::Red,"Found InteractableActor");
		IInteractionInterface::Execute_Interact(FoundInteractableActor,this);
	}
}


//Server RPC Implementation, can be called by the client.
void AJumpingToConclusionsCharacter::ServerAnswerToPuzzle_Implementation(int32 SubmittedAnswer,int32 AnswerIndex)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red,
FString::Printf(TEXT("AnswerInput %d"), SubmittedAnswer));
	if (AJTCGameState* CustomGameState = Cast<AJTCGameState>(GetWorld()->GetGameState()))
	{
		if (CustomGameState->AnswerSheet[AnswerIndex] == SubmittedAnswer)
		{
			UE_LOG(LogTemp, Warning, TEXT("Authority: %d"), CustomGameState->HasAuthority());
			CustomGameState->AddSolvedPuzzleScore(true);
		}
		else
		{
			CustomGameState->AddSolvedPuzzleScore(false);
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Failed Cast to gamestate");
	}
}

void AJumpingToConclusionsCharacter::ServerCastMatchTest_Implementation()
{

}


void AJumpingToConclusionsCharacter::ClientRPCFunction_Implementation()
{
	UNiagaraComponent* NiagaraEffect = UNiagaraFunctionLibrary::SpawnSystemAtLocation(
		GetWorld(),
		ClientParticleEffect,
		this->GetActorLocation());
}
