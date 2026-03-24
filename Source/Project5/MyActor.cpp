// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"
#include "Engine/Engine.h"

// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	TotalDistance = 0.0f;
	EventCount = 0;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualMesh"));
	RootComponent = Mesh;

}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();
	
	FVector StartPos(0.0f, 50.0f, 0.0f);
	SetActorLocation(StartPos);
	LastLocation = StartPos;
	UE_LOG(LogTemp, Log, TEXT("=== Move Start ==="));

	for (int32 i = 1; i <= 10; ++i)
	{
		Move(i);
		EventCount += TriggerEvent();
		Turn();
	}
	UE_LOG(LogTemp, Error, TEXT("====================================="));
	UE_LOG(LogTemp, Error, TEXT("Total Distance: %.2f"), TotalDistance);
	UE_LOG(LogTemp, Error, TEXT("Event Count: %d"), EventCount);
	UE_LOG(LogTemp, Error, TEXT("====================================="));
	
}

void AMyActor::Move(int32 Step)
{
	FVector CurrentPos = GetActorLocation();
	float RandX = FMath::RandRange(-100.0f, 100.0f);
	float RandY = FMath::RandRange(-100.0f, 100.0f);
	FVector NewPos = CurrentPos + FVector(RandX, RandY, 0.0f);

	SetActorLocation(NewPos);
	float StepDistance = FVector::Dist(LastLocation, NewPos);
	TotalDistance += StepDistance;
	
	UE_LOG(LogTemp, Warning, TEXT("[%d] Location: %s (Move : %.2f)"),
		Step, *NewPos.ToString(), StepDistance);

	LastLocation = NewPos;
}

int32 AMyActor::TriggerEvent()
{
	// [50% 확률 이벤트 시스템] 0 또는 1 랜덤 생성
	int32 RandomVal = FMath::RandRange(0, 1);

	if (RandomVal == 1)
	{
		UE_LOG(LogTemp, Log, TEXT(" Event Count."));
		return 1;
	}

	UE_LOG(LogTemp, Log, TEXT(" Event No Count."));
	return 0;
}

void AMyActor::Turn()
{
	float RandomYaw = FMath::FRandRange(0.0f, 360.0f);
	FRotator NewRotation = GetActorRotation() + FRotator(0.0f, RandomYaw, 0.0f);
	SetActorRotation(NewRotation);

	UE_LOG(LogTemp, Log, TEXT("Rotation: %s"), *NewRotation.ToString());
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

