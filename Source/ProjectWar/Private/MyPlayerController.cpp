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
	}
}


void AMyPlayerController::MovementCameraTriggered()
{
	CurrentMousePosition = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld());
	FVector2D MinusCurrentAndStartMousePositions = (CurrentMousePosition - StartMousePosition);
	Result = FVector(MinusCurrentAndStartMousePositions.X*10.0f, MinusCurrentAndStartMousePositions.Y*10.0f, 0);
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