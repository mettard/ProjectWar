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

// Called when the game starts or when spawned
void ACPP_CameraCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACPP_CameraCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACPP_CameraCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("Zoom", this, &ACPP_CameraCharacter::Zoom);

}

void ACPP_CameraCharacter::Zoom(float AxisValue)
{
	SpringArm->TargetArmLength = SpringArm->TargetArmLength + AxisValue * 100;
}

