// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIControllerBase.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTWAR_API AAIControllerBase : public AAIController
{
	GENERATED_BODY()
	
protected:
	FGenericTeamId TeamId;
	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;

public:
	virtual FGenericTeamId GetGenericTeamId() const override { return TeamId; };
	virtual void BeginPlay() override;
};
