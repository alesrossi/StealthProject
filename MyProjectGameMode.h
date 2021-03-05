// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Grid.h"
#include "GameFramework/GameModeBase.h"
#include "MyProjectGameMode.generated.h"

UCLASS(minimalapi)
class AMyProjectGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AMyProjectGameMode();

	UPROPERTY()
	int32 MaxCols;
	
	UPROPERTY()
	int32 MaxRows;
	
	UPROPERTY()
	float Distance;
	
	TArray<FInnerArray> listOfWaypoints;

	UPROPERTY(EditAnywhere)
	int32 MaxSentinels;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class ASentinel> ToSpawnSentinel;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AActor> ToSpawnCrystal;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};



