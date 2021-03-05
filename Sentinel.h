// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Sentinel.generated.h"

UCLASS()
class MYPROJECT_API ASentinel : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASentinel();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, Category= "AI")
	class UBehaviorTree* BehaviorTree;

	UPROPERTY(VisibleAnywhere, Category="AI")
	class UPawnSensingComponent* PawnSensingComp;
	
	int32 x_value;
	int32 y_value;

	UPROPERTY(EditAnywhere)
	float runSpeed;
	
	private:
	
	UFUNCTION()
	void OnPlayerCaught(APawn* Pawn);
};
