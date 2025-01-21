// Fill out your copyright notice in the Description page of Project Settings.


#include "AIControllerBase.h"
#include "CharacterBase.h"




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
	const AActor* OtherPawn = Cast<AActor>(&Other);
	if (OtherPawn == nullptr)
	{return ETeamAttitude::Neutral;}

	//Check if actor implements GenericTeamAgentInterface
	const class IGenericTeamAgentInterface* PlayerTi = Cast<IGenericTeamAgentInterface>(&Other);
	const class IGenericTeamAgentInterface* BotTi = Cast<IGenericTeamAgentInterface>(OtherPawn); 
	if (BotTi == nullptr && PlayerTi == nullptr)
	{return ETeamAttitude::Neutral;} 


	//Get Actor's TeamID
	FGenericTeamId OtherActorTeamID = NULL;
	if (BotTi != nullptr)
	{OtherActorTeamID = BotTi->GetGenericTeamId();}
	else if (PlayerTi != nullptr)
	{OtherActorTeamID = PlayerTi->GetGenericTeamId();}
	
	//Check if Hostile
	const FGenericTeamId ThisID = GetGenericTeamId();
	if (OtherActorTeamID == 8)
	{return ETeamAttitude::Neutral;}
	if (OtherActorTeamID == ThisID)
	{return ETeamAttitude::Friendly;}
	if (OtherActorTeamID != ThisID)
	{return ETeamAttitude::Hostile;}
	return ETeamAttitude::Neutral;
}



