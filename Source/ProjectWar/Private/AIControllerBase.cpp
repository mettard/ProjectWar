// Fill out your copyright notice in the Description page of Project Settings.


#include "AIControllerBase.h"
#include "CharacterBase.h"




void AAIControllerBase::BeginPlay()
{
	Super::BeginPlay();
	if (const ACharacterBase* Chr = Cast<ACharacterBase>(GetPawn()))
	{
		TeamId = FGenericTeamId(Chr->ID);
	}
}

ETeamAttitude::Type AAIControllerBase::GetTeamAttitudeTowards(const AActor& Other) const
{
	//Check if Pawn
	const APawn* OtherPawn = Cast<APawn>(&Other);
	if (OtherPawn == nullptr)
	{return ETeamAttitude::Neutral;}

	
	//Check if actor implements GenericTeamAgentInterface
	const auto PlayerTi = Cast<IGenericTeamAgentInterface>(&Other); // I think error because i cant normally cast
	const class IGenericTeamAgentInterface* BotTi = Cast<IGenericTeamAgentInterface>(OtherPawn->GetController()); // I think error because i cant normally cast
	if (BotTi == nullptr && PlayerTi == nullptr)
	{return ETeamAttitude::Neutral;} 
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Example text that prints a float"), (PlayerTi));


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
	else if (OtherActorTeamID == ThisID)
	{return ETeamAttitude::Friendly;}
	else
	{return ETeamAttitude::Hostile;}
}



