// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAIController.h"
#include "MyProjectGameMode.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"


AEnemyAIController::AEnemyAIController()
{
	BehaviorTreeComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviourTreeComp"));
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackBoardComp"));
	PrimaryActorTick.bCanEverTick = true;
	bAllowStrafe = true;
	
	PlayerKey = "Target";
	LocationToGoKey = "LocationToGo";
	
	isRoaming = true;
	
}

void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();

}

void AEnemyAIController::Tick(float DeltaTime)
{
}

void AEnemyAIController::SetPlayerCaught(APawn* pawn)
{
	if(BlackboardComp)
	{
		BlackboardComp->SetValueAsObject(PlayerKey, pawn);
	}
}

void AEnemyAIController::SetCloseNodes()
{
	
	UWorld* const World = GetWorld();
	AMyProjectGameMode* GM = World->GetAuthGameMode<AMyProjectGameMode>();
	int i = owner->y_value;
	int j = owner->x_value;
	
	
	CloseNodes.Empty();
	if(i > 0)
	{
		CloseNodes.Add(GM->listOfWaypoints[i-1][j]); //North Node
	}
	if(j < GM->MaxCols-1)
	{
		CloseNodes.Add(GM->listOfWaypoints[i][j+1]);  //East Node
	}
	if(i < GM->MaxCols-1)
	{
		CloseNodes.Add(GM->listOfWaypoints[i+1][j]);  //South Node
	}
	if(j > 0)
	{
		CloseNodes.Add(GM->listOfWaypoints[i][j-1]);  //West Node
	}

	
}

void AEnemyAIController::OnPossess(APawn* pawn)
{
	Super::OnPossess(pawn);
	
	UWorld* const World = GetWorld();
	owner = Cast<ASentinel>(pawn);

	if(owner)
	{	
		if(owner->BehaviorTree->BlackboardAsset)
		{
			BlackboardComp->InitializeBlackboard(*(owner->BehaviorTree->BlackboardAsset));
		}

		BehaviorTreeComp->StartTree(*owner->BehaviorTree);
	}
}
