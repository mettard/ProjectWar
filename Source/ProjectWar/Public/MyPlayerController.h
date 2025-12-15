// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "CPP_CameraCharacter.h"
#include "BaseWidgetBlueprint.h"
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
	// Функція повертає true, якщо було влучання (Hit)
	UFUNCTION(BlueprintCallable, Category = "Raycast")
	bool TraceFromMouse(float TraceDistance, FHitResult& OutHit);
	// Змінна для зберігання класу, з яким будемо порівнювати (сюди оберете BP_TestVehicle в редакторі)
	UPROPERTY(EditAnywhere, Category = "Config")
	TSubclassOf<AActor> TargetClass;

	
	

protected:
	// Calls on the start of the game
	virtual void BeginPlay() override;
	// Called for movement input
	void MovementCameraTriggered();
	void MovementCameraStarted();
	void MovementCameraCanceled();
	void MovementCameraCompleted();
	void HoldingCtrlStarted();
	void HoldingCtrlOngoing();
	void HoldingCtrlCanceled();
	void HoldingCtrlCompleted();
	void HoldingShiftStarted();
	void HoldingShiftOngoing();
	void HoldingShiftCanceled();
	void HoldingShiftCompleted();
	void SendingUnitTriggered();
	void SelectionActorTriggered();

	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	class UInputMappingContext* NewInputMappingContext;
	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	class UInputAction* MovingCamera;
	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	class UInputAction* SendingUnit;
	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	class UInputAction* SelectionActor;
	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	class UInputAction* HoldingCtrl;
	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	class UInputAction* HoldingShift;




private:
	FVector Result;
	FVector2D CurrentMousePosition;
	FVector2D StartMousePosition;
	bool bHoldingCtrl;
	bool bHoldingShift;
	bool bSelectedActorsCleared;
	FHitResult HitResult;
	AActor* HitActor;
	AActor* HittedActor;
	TArray<AActor*> SelectedActors;
};
