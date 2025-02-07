// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/AIModule/Classes/GenericTeamAgentInterface.h"
#include "GameFramework/Character.h"
#include "CharacterBase.generated.h"

UCLASS()
class PROJECTWAR_API ACharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FGenericTeamId teamID;
	
	// Sets default values for this character's properties
	ACharacterBase();
	
	// UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	// int32 ID;

	virtual FGenericTeamId GetGenericTeamId() const { return teamID; }

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Gameplay")
	int32 HP;


	
};
