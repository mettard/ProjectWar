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

	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ZoomTimelineComp = CreateDefaultSubobject<UTimelineComponent>(TEXT("ZoomTimelineComp"));
}
// Called to bind functionality to input
void ACPP_CameraCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("Zoom", this, &ACPP_CameraCharacter::Zoom);
}

void ACPP_CameraCharacter::BeginPlay()
{
	Super::BeginPlay();
	FOnTimelineFloat ProgressUpdate;
	ProgressUpdate.BindUFunction(this, FName("Zoom"));

	FOnTimelineEvent FinishedEvent;
	FinishedEvent.BindUFunction(this, FName("ZoomFinished"));

	ZoomTimeline.SetTimelineFinishedFunc(FinishedEvent);
	ZoomTimeline.SetFloatCurve(ZoomCurve, "None");
}

// Called to Zoom Camera In or Out
void ACPP_CameraCharacter::Zoom(float AxisValue)
{
	Camera->OrthoWidth = FMath::Clamp(Camera->OrthoWidth, 400, 30000);
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Some debug message!"));
	if (Camera->OrthoWidth >= 400 && Camera->OrthoWidth <= 2000)
	{
		Camera->OrthoWidth += AxisValue * 100;
		ZoomTimeline.Play();
	}
	if (Camera->OrthoWidth >= 2001 && Camera->OrthoWidth <= 6000)
	{
		Camera->OrthoWidth += AxisValue * 300;
		ZoomTimeline.Play();
	}
	if (Camera->OrthoWidth >= 6001 && Camera->OrthoWidth <= 20000)
	{
		Camera->OrthoWidth += AxisValue * 1400;
		ZoomTimeline.Play();
	}
	if (Camera->OrthoWidth >= 20001 && Camera->OrthoWidth <= 30000)
	{
		Camera->OrthoWidth += AxisValue * 2000;
		ZoomTimeline.Play();
	}
}

void ACPP_CameraCharacter::ZoomFinished()
{
}

