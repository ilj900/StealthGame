// Fill out your copyright notice in the Description page of Project Settings.


#include "BlackHole.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABlackHole::ABlackHole()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Singularity = CreateDefaultSubobject<USphereComponent>(TEXT("Singularity"));
	Singularity->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Singularity->SetCollisionResponseToAllChannels(ECR_Ignore);
	Singularity->SetCollisionResponseToChannel(ECC_PhysicsBody, ECR_Overlap);
	RootComponent = Singularity;

	AttractionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("AttractionSphere"));
	AttractionSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	AttractionSphere->SetCollisionResponseToAllChannels(ECR_Ignore);
	AttractionSphere->SetCollisionResponseToChannel(ECC_PhysicsBody, ECR_Overlap);
	AttractionSphere->SetupAttachment(Singularity);

	EventHorizon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EventHorizon"));
	EventHorizon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	EventHorizon->SetupAttachment(Singularity);
}

// Called when the game starts or when spawned
void ABlackHole::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABlackHole::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TArray<AActor*> AllOverlapingActors;
	Singularity->GetOverlappingActors(AllOverlapingActors);
	for (auto& Actor : AllOverlapingActors)
	{
		Actor->Destroy();
	}

	TArray<UPrimitiveComponent*> AllActorsInRange;
	AttractionSphere->GetOverlappingComponents(AllActorsInRange);
	for (auto& Actor : AllActorsInRange)
	{
		auto PrimitiveComponent = Cast<UPrimitiveComponent>(Actor);
		if (PrimitiveComponent && PrimitiveComponent->IsSimulatingPhysics())
		{
			auto ForceDirection = AttractionSphere->GetComponentLocation() - PrimitiveComponent->GetComponentLocation();
			PrimitiveComponent->AddForce(ForceDirection.GetSafeNormal() * GraviryForce);
		}
	}

	
}

