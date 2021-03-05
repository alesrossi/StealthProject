// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "WayPoint.h"
#include "GameFramework/Actor.h"
#include "Grid.generated.h"

USTRUCT()
struct FInnerArray
{
	GENERATED_BODY()

	TArray<AActor*> inner;

	AActor* operator[] (int32 i)
	{
		return inner[i];
	}

	void Add(AActor* wp)
	{
		inner.Add(wp);
	}
	
};

UCLASS()
class MYPROJECT_API AGrid : public AActor
{
	GENERATED_BODY()
			
public:	
	// Sets default values for this actor's properties
	AGrid();

	virtual bool ShouldTickIfViewportsOnly() const override;
	
	UPROPERTY(EditAnywhere)
	int32 MaxCols;
	
	UPROPERTY(EditAnywhere)
    int32 MaxRows;
	
	UPROPERTY(EditAnywhere)
	float Distance;
	
	TArray<FInnerArray> listOfWaypoints;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AWayPoint> ToSpawn;

	UFUNCTION(BlueprintCallable, CallInEditor)
    void CreateGrid();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

