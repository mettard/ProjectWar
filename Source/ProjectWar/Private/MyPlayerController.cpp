// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "Engine/Engine.h"
#include "Runtime/UMG/Public/Blueprint/WidgetLayoutLibrary.h"
#include "Runtime/Engine/Classes/Kismet/KismetMathLibrary.h"
#include "InputMappingContext.h"

AMyPlayerController::AMyPlayerController()
{

};


void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetupPlayerInputComponent(InputComponent);
	bShowMouseCursor = true;
}

// Called to set up input actions
void AMyPlayerController::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	if (APlayerController* PlayerController = Cast<APlayerController>(this))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(NewInputMappingContext, 0);
		}
	}
	if (UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		Input->BindAction(MovingCamera, ETriggerEvent::Triggered, this, &AMyPlayerController::MovementCameraTriggered);
		Input->BindAction(MovingCamera, ETriggerEvent::Started, this, &AMyPlayerController::MovementCameraStarted);
		Input->BindAction(MovingCamera, ETriggerEvent::Canceled, this, &AMyPlayerController::MovementCameraCanceled);
		Input->BindAction(MovingCamera, ETriggerEvent::Completed, this, &AMyPlayerController::MovementCameraCompleted);
	}
}


void AMyPlayerController::MovementCameraTriggered()
{
	if (APlayerController* PlayerController = Cast<APlayerController>(this))
	{
		FVector WorldLocation;
		FVector WorldDirection;
		/*FHitResult OutHit;
		FCollisionQueryParams CollisionParams;*/
		PlayerController->DeprojectMousePositionToWorld(WorldLocation, WorldDirection);
		FVector EndPoint = WorldDirection * 10000.f + WorldLocation;

		//Maybe if I will make every blueprint into c++, this will help me
		
		/*DrawDebugLine(GetWorld(), WorldLocation, EndPoint, FColor::Green, true, 2.f, false, 4.f);
		GetWorld()->LineTraceSingleByChannel(OutHit, WorldLocation, EndPoint, ECC_WorldDynamic, CollisionParams);

		if (OutHit.GetActor()) 
		{

		}*/
	}

	
	CurrentMouseCursor = EMouseCursor::Hand;
	CurrentMousePosition = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld());
	FVector2D MinusCurrentAndStartMousePositions = (CurrentMousePosition - StartMousePosition);
	ACPP_CameraCharacter* CameraCharacter = Cast<ACPP_CameraCharacter>(GetPawn());
	if (CameraCharacter)
	{
		float CameraCharacterZoom =	CameraCharacter->Camera->OrthoWidth;
		if (CameraCharacterZoom <= 2000)
		{
			Result = FVector(MinusCurrentAndStartMousePositions.X*1.0f, MinusCurrentAndStartMousePositions.Y*1.0f, 0);
		}
		if (CameraCharacterZoom >= 2001 && CameraCharacterZoom <= 6000)
		{
			Result = FVector(MinusCurrentAndStartMousePositions.X*3.0f, MinusCurrentAndStartMousePositions.Y*3.0f, 0);
		}
		if (CameraCharacterZoom >= 6001 && CameraCharacterZoom <= 15000)
		{
			Result = FVector(MinusCurrentAndStartMousePositions.X*10.0f, MinusCurrentAndStartMousePositions.Y*10.0f, 0);
		}
		if (CameraCharacterZoom >= 15001)
		{
			Result = FVector(MinusCurrentAndStartMousePositions.X*20.0f, MinusCurrentAndStartMousePositions.Y*20.0f, 0);
		}
		
	}
	//Result = FVector(MinusCurrentAndStartMousePositions.X*10.0f, MinusCurrentAndStartMousePositions.Y*10.0f, 0);
	if (APawn* ControlledPawn = GetPawn())
	{
		ControlledPawn->AddActorWorldOffset(Result);
	}
	StartMousePosition = CurrentMousePosition;
}

void AMyPlayerController::MovementCameraStarted()
{
	StartMousePosition = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld());
}

void AMyPlayerController::MovementCameraCanceled()
{
	CurrentMouseCursor = EMouseCursor::Default;
}

void AMyPlayerController::MovementCameraCompleted()
{
	CurrentMouseCursor = EMouseCursor::Default;
}


