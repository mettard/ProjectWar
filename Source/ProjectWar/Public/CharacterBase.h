// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/AIModule/Classes/Perception/AISightTargetInterface.h"
#include "Runtime/AIModule/Classes/GenericTeamAgentInterface.h"
#include "GameFramework/Character.h"
#include "CharacterBase.generated.h"

UCLASS()
class PROJECTWAR_API ACharacterBase : public ACharacter, public IAISightTargetInterface, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacterBase();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	int32 ID = 0;

	virtual FGenericTeamId GetGenericTeamId() const override { return teamID; }

protected:
	FGenericTeamId teamID;
	
};
