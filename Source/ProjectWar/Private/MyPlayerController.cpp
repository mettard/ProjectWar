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





bool AMyPlayerController::TraceFromMouse(float TraceDistance, FHitResult& OutHit)
{
	// 1. Отримуємо контролер гравця
	APlayerController* PlayerController = Cast<APlayerController>(this);
	if (!PlayerController)
	{
		return false; // Контролер не знайдено
	}

	// 2. Змінні для збереження результату депроєкції
	FVector WorldLocation;
	FVector WorldDirection;

	// Це прямий аналог ноди "Convert Mouse Location To World Space"
	bool bDeprojectSuccess = PlayerController->DeprojectMousePositionToWorld(WorldLocation, WorldDirection);

	if (bDeprojectSuccess)
	{
		// 3. Розрахунок старту та кінця (аналог математики на скріншоті)
		FVector Start = WorldLocation;
		FVector End = Start + (WorldDirection * TraceDistance); // TraceDistance це ваші 10000.0

		// 4. Налаштування параметрів трейсу
		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(this); // Аналог галочки "Ignore Self"

		// 5. Виконання Line Trace (Channel: Visibility)
		bool bHit = GetWorld()->LineTraceSingleByChannel(
			OutHit, 
			Start, 
			End, 
			ECC_Visibility, 
			QueryParams
		);

		// (Опціонально) Малюємо лінію для дебагу, щоб бачити промінь
		// DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 2.0f);

		return bHit;
	}

	return false;
}

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
		Input->BindAction(MovingCamera, ETriggerEvent::Canceled, this, &AMyPlayerController::MovementCameraCanceled);
		Input->BindAction(MovingCamera, ETriggerEvent::Completed, this, &AMyPlayerController::MovementCameraCompleted);

		
		Input->BindAction(HoldingCtrl, ETriggerEvent::Started, this, &AMyPlayerController::HoldingCtrlStarted);
		Input->BindAction(HoldingCtrl, ETriggerEvent::Ongoing, this, &AMyPlayerController::HoldingCtrlOngoing);
		Input->BindAction(HoldingCtrl, ETriggerEvent::Canceled, this, &AMyPlayerController::HoldingCtrlCanceled);
		Input->BindAction(HoldingCtrl, ETriggerEvent::Completed, this, &AMyPlayerController::HoldingCtrlCompleted);
		
		Input->BindAction(HoldingShift, ETriggerEvent::Started, this, &AMyPlayerController::HoldingShiftStarted);
		Input->BindAction(HoldingShift, ETriggerEvent::Ongoing, this, &AMyPlayerController::HoldingShiftOngoing);
		Input->BindAction(HoldingShift, ETriggerEvent::Canceled, this, &AMyPlayerController::HoldingShiftCanceled);
		Input->BindAction(HoldingShift, ETriggerEvent::Completed, this, &AMyPlayerController::HoldingShiftCompleted);

		
		Input->BindAction(SelectionActor, ETriggerEvent::Triggered, this, &AMyPlayerController::SelectionActorTriggered);
		//Input->BindAction(SendingUnit, ETriggerEvent::Triggered, this, &AMyPlayerController::SendingUnitTriggered); Continue, when i will make Selected Actors array
	}
}

void AMyPlayerController::SelectionActorTriggered()
{
	if (TraceFromMouse(0, HitResult))
	{
		HitActor = HitResult.GetActor();
	}
	
	if (bHoldingCtrl == true)
	{
		SelectedActors.RemoveAt(SelectedActors.Find(HitActor));
	}
	else
	{
		if (bHoldingShift == true)
		{
			SelectedActors.Insert(HitActor,0);
		}
		else
		{
			if (HitActor->GetClass() == TargetClass)
			{
				HittedActor = HitActor;
				if (SelectedActors[0] != HittedActor)
				{
					SelectedActors.RemoveAt(SelectedActors.Find(SelectedActors[0]));
					SelectedActors.Insert(HittedActor,0);
					GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("This is the pre-set text"));
					
					// Далі треба буде тут дописати логіку для віджета
				}
				else
				{
					SelectedActors.Insert(HittedActor,0);
				}
			}
			else
			{
				for (int32 i = 0; i < SelectedActors.Num(); ++i)
				{
					AActor* Actor = SelectedActors[i];
					if (Actor)
					{
						SelectedActors.Empty();
						bSelectedActorsCleared = true;
					}
				}
			}
		}
	}
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("This is the pre-set text"));
}
/*Continue, when i will make Selected Actors array
void AMyPlayerController::SendingUnitTriggered()
{
	bool bIsMoving = false;
	if (bIsMoving == false)
	{
		//IsValid()
	}
}*/

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
		ControlledPawn->AddActorWorldOffset(Result, true);
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

void AMyPlayerController::HoldingCtrlStarted()
{
	bHoldingCtrl = true;
}
void AMyPlayerController::HoldingCtrlOngoing()
{
	bHoldingCtrl = true;
}
void AMyPlayerController::HoldingCtrlCanceled()
{
	bHoldingCtrl = false;
}
void AMyPlayerController::HoldingCtrlCompleted()
{
	bHoldingCtrl = false;
}

void AMyPlayerController::HoldingShiftStarted()
{
	bHoldingShift = true;
}
void AMyPlayerController::HoldingShiftOngoing()
{
	bHoldingShift = true;
}
void AMyPlayerController::HoldingShiftCanceled()
{
	bHoldingShift = false;
}
void AMyPlayerController::HoldingShiftCompleted()
{
	bHoldingShift = false;
}




