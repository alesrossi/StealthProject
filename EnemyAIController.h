// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Sentinel.h"
#include "WayPoint.h"
#include "BehaviorTree/BehaviorTreeComponent.h"

#include "EnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()
	
	UBehaviorTreeComponent* BehaviorTreeComp;
	UBlackboardComponent* BlackboardComp;

	UPROPERTY(EditDefaultsOnly, Category="AI")
	FName LocationToGoKey;

	UPROPERTY(EditDefaultsOnly, Category="AI")
	FName PlayerKey;
	

	virtual void OnPossess(APawn* Pawn) override;

	public:

	AEnemyAIController();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;
	
	void SetPlayerCaught(APawn* Pawn);

	void SetCloseNodes();

	TArray<AActor*> CloseNodes;

	bool isRoaming;
	
	ASentinel* owner;

	FORCEINLINE UBlackboardComponent* GetBlackBoardComp() const {return BlackboardComp; }
	FORCEINLINE TArray<AActor*> GetCloseNodes() const { return CloseNodes; }

	private:
	
	FVector Next;

};
