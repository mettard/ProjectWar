// Fill out your copyright notice in the Description page of Project Settings.
#include "CharacterBase.h"
#include "AIControllerBase.h"




void AAIControllerBase::BeginPlay()
{
	Super::BeginPlay();
	if (const ACharacterBase* Chr = Cast<ACharacterBase>(GetPawn()))
	{
		TeamId = FGenericTeamId(Chr->teamID);
	}
	
}

ETeamAttitude::Type AAIControllerBase::GetTeamAttitudeTowards(const AActor& Other) const
{
	//Check if Pawn
	const APawn* OtherPawn = Cast<APawn>(&Other);
	if (OtherPawn == nullptr)
	{return ETeamAttitude::Neutral;}

	//Check if actor implements GenericTeamAgentInterface
	auto PlayerTi = Cast<IGenericTeamAgentInterface>(&Other);
	class IGenericTeamAgentInterface* BotTi = Cast<IGenericTeamAgentInterface>(OtherPawn->GetController()); 
	if (BotTi == nullptr && PlayerTi == nullptr)
	{return ETeamAttitude::Neutral;} 


	//Get Actor's TeamID
	FGenericTeamId OtherActorTeamID = NULL;
	if (BotTi != nullptr)
	{OtherActorTeamID = BotTi->GetGenericTeamId();}
	if (PlayerTi != nullptr)
	{OtherActorTeamID = PlayerTi->GetGenericTeamId();}
	
	//Check if Hostile
	const FGenericTeamId ThisID = GetGenericTeamId();
	if (OtherActorTeamID == 8)
	{return ETeamAttitude::Neutral;}
	else if (OtherActorTeamID == ThisID)
	{return ETeamAttitude::Friendly;}
	else
	{return ETeamAttitude::Hostile;}
}


