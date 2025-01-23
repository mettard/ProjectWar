// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "MyPlayerController.generated.h"


/**
 * 
 */
UCLASS()
class PROJECTWAR_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
	

public:
	// Constructor
	AMyPlayerController();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent);

protected:
	// Calls on the start of the game
	virtual void BeginPlay() override;
	// Called for movement input
	void MovementCameraTriggered();
	void MovementCameraStarted();
	void MovementCameraCanceled();
	void MovementCameraCompleted();

	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	class UInputMappingContext* NewInputMappingContext;

	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	class UInputAction* MovingCamera;





private:
	FVector Result;
	FVector2D CurrentMousePosition;
	FVector2D StartMousePosition;
};
