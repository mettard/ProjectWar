// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_CameraCharacter.h"

// Sets default values
ACPP_CameraCharacter::ACPP_CameraCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpingArmComponent"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("MainCamera"));
	Camera->SetupAttachment(SpringArm);

}
// Called to bind functionality to input
void ACPP_CameraCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("Zoom", this, &ACPP_CameraCharacter::Zoom);

}
// Called to Zoom Camera In or Out
void ACPP_CameraCharacter::Zoom(float AxisValue)
{
	SpringArm->TargetArmLength = SpringArm->TargetArmLength + AxisValue * 200;
}

