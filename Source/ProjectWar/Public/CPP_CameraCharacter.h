// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include <GameFramework/SpringArmComponent.h>
#include <Camera/CameraComponent.h>
#include "CPP_CameraCharacter.generated.h"

UCLASS()
class PROJECTWAR_API ACPP_CameraCharacter : public ACharacter
{
	GENERATED_BODY()

public:	
	// Sets default values for this character's properties
	ACPP_CameraCharacter();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	UPROPERTY(VisibleAnywhere);
		USpringArmComponent* SpringArm;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Camera");
		UCameraComponent* Camera;
	


private:

	void Zoom(float AxisValue);
};
