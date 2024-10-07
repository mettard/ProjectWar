// Fill out your copyright notice in the Description page of Project Settings.

#include "MyPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"



AMyPlayerController::AMyPlayerController()
{

};

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();

}



void AMyPlayerController::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerConroller->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(NewInputMappingContext, 0);
		}
	}
	if (UEnhancedInputComponent* Input = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		Input->BindAction(NewInputMappingContext, ETriggerEvent::Triggered, this, &AMyPlayerController::MovementCamera);
	}
}

void AMyPlayerController::MovementCamera(const FInputActionValue& Value)
{
}