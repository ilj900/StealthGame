// Fill out your copyright notice in the Description page of Project Settings.

#include "LaunchPad.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/DecalComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ALaunchPad::ALaunchPad()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = StaticMesh;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetupAttachment(StaticMesh);
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ALaunchPad::HandleOverlap);
}

void ALaunchPad::HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto OtherCharacter = Cast<ACharacter>(OtherActor);
	if (OtherCharacter)
	{
		OtherCharacter->LaunchCharacter((GetActorForwardVector() + FVector(0.f, 0.f, 1.f)) * LaunchForce, false, false);
		PlayEffects();
		return;
	}
	if (OtherComp)
	{
		OtherComp->AddImpulse((GetActorForwardVector() + FVector(0.f, 0.f, 1.f)) * LaunchForce * 500.f);
		PlayEffects();
	}
}

void ALaunchPad::PlayEffects() const
{
	UGameplayStatics::SpawnEmitterAtLocation(this, LaunchFX, GetActorLocation());
}
