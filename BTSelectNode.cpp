// Fill out your copyright notice in the Description page of Project Settings.


#include "BTSelectNode.h"

#include "EnemyAIController.h"
#include "MyProjectGameMode.h"
#include "WayPoint.h"
#include "BehaviorTree/BlackboardComponent.h"


EBTNodeResult::Type UBTSelectNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AMyProjectGameMode* GM = GetWorld()->GetAuthGameMode<AMyProjectGameMode>();
	AEnemyAIController* SentinelController = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
	ASentinel* Sentinel = Cast<ASentinel>(SentinelController->owner);

	if(SentinelController)
	{
		UBlackboardComponent* BlackboardComp = SentinelController->GetBlackBoardComp();

		AWayPoint* CurrentPoint = Cast<AWayPoint>(BlackboardComp->GetValueAsObject("LocationToGo"));
		
		CurrentPoint = Cast<AWayPoint>(GM->listOfWaypoints[Sentinel->y_value][Sentinel->x_value]); //Initialize current Node
		SentinelController->SetCloseNodes();

		AWayPoint* NextPoint = nullptr;

		if(SentinelController->isRoaming)
		{
			NextPoint = Cast<AWayPoint>(SentinelController->CloseNodes[FMath::RandRange(0, SentinelController->CloseNodes.Num()-1)]); //Iniziatlize Next node

			for(int i=0; i<GM->MaxRows; i++)
			{
				for(int j=0; j<GM->MaxCols; j++)
				{
					if(GM->listOfWaypoints[i][j] == NextPoint)
					{
						Sentinel->x_value = j;
						Sentinel->y_value = i;
						break;
					}
				}
			}

		}

		
		BlackboardComp->SetValueAsObject("LocationToGo", NextPoint);

		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}
