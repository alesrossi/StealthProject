// Fill out your copyright notice in the Description page of Project Settings.


#include "Sentinel.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnemyAIController.h"
#include "Perception/PawnSensingComponent.h"

// Sets default values
ASentinel::ASentinel()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));
	PawnSensingComp->SetPeripheralVisionAngle(90.f);

	runSpeed = 450.f;
}

// Called when the game starts or when spawned
void ASentinel::BeginPlay()
{
	Super::BeginPlay();

	if(PawnSensingComp)
	{
		PawnSensingComp->OnSeePawn.AddDynamic(this, &ASentinel::OnPlayerCaught);
	}
	
}

// Called every frame
void ASentinel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASentinel::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ASentinel::OnPlayerCaught(APawn* Pawn)
{
	AEnemyAIController* SentinelController = Cast<AEnemyAIController>(GetController());

	if(SentinelController)
	{
		UCharacterMovementComponent *MovementPtr =  Cast<UCharacterMovementComponent>(GetCharacterMovement());
		MovementPtr->MaxWalkSpeed = runSpeed;  //if player spotted set speed to running
		
		UE_LOG(LogTemp, Warning, TEXT("player caught"))
		SentinelController->SetPlayerCaught(Pawn);
	}
}

