// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyProjectGameMode.h"

#include "EnemyAIController.h"
#include "Math/UnrealMathUtility.h"
#include "Grid.h"
#include "Sentinel.h"
#include "UObject/ConstructorHelpers.h"

AMyProjectGameMode::AMyProjectGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	MaxSentinels = 4;
	MaxCols = 9;
	MaxRows = 9;
	Distance = 630.f;


	
}

// Called when the game starts or when spawned
void AMyProjectGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	UWorld* const World = GetWorld();
	if(World)
	{
		FRotator Rotation(0.0f, 0.0f, 0.0f);
		for (int k=0; k<MaxSentinels; k++)
		{
			int32 i = FMath::RandRange(0, MaxCols-1);
			int32 j = FMath::RandRange(0, MaxRows-1);

			FVector SpawnLoc = listOfWaypoints[i][j]->GetActorLocation();
			
			ASentinel* newSentinel = World->SpawnActor<ASentinel>(ToSpawnSentinel, SpawnLoc, Rotation);
			
			newSentinel->x_value = j;
			newSentinel->y_value = i;
		}

		FVector endLoc = listOfWaypoints[ FMath::RandRange(0, MaxCols-1)][ FMath::RandRange(0, MaxCols-1)]->GetActorLocation();
		World->SpawnActor<AActor>(ToSpawnCrystal, endLoc, Rotation);
		
	}
	
}