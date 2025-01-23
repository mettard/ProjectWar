// Fill out your copyright notice in the Description page of Project Settings.


#include "MainParentClassForVehicles.h"

// Sets default values
AMainParentClassForVehicles::AMainParentClassForVehicles()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMainParentClassForVehicles::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMainParentClassForVehicles::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMainParentClassForVehicles::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

