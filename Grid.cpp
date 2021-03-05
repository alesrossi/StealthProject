// Fill out your copyright notice in the Description page of Project Settings.


#include "Grid.h"

#include "DrawDebugHelpers.h"
#include "MyProjectGameMode.h"

// Sets default values
AGrid::AGrid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

bool AGrid::ShouldTickIfViewportsOnly() const
{
	return true;
}

// Called when the game starts or when spawned
void AGrid::BeginPlay()
{
	Super::BeginPlay();

	UWorld* const World = GetWorld();
	if(AMyProjectGameMode* GM = World->GetAuthGameMode<AMyProjectGameMode>())
	{
		MaxCols = GM->MaxCols;
		MaxRows = GM->MaxRows;
		Distance = GM->Distance;
	}
	
	CreateGrid();

	
}

void AGrid::CreateGrid()
{
	FVector HorizonalVector(Distance, 0.f, 0.f);
	FVector VerticalVector(0.f, Distance, 0.f);

	UWorld* const World = GetWorld();
	FRotator Rotation(0.0f, 0.0f, 0.0f);
	
	for (int i=0; i<MaxRows; i++)
	{
		listOfWaypoints.Add(FInnerArray());
		FVector locout= GetActorLocation();
		
		for(int j=0; j<MaxCols; j++)
		{
			FVector loc= GetActorLocation();
			AWayPoint* newWayPoint = World->SpawnActor<AWayPoint>(ToSpawn, loc, Rotation);
			
			listOfWaypoints[i].Add(newWayPoint);
			
			SetActorLocation(loc + HorizonalVector, false);
		}
		

		SetActorLocation(locout + VerticalVector, false);
	}
	
	if(AMyProjectGameMode* GM = World->GetAuthGameMode<AMyProjectGameMode>())
	{
		GM->listOfWaypoints = listOfWaypoints;
	}
	
}

// Called every frame
void AGrid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

