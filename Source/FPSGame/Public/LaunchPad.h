// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LaunchPad.generated.h"

class UStaticMeshComponent;
class UBoxComponent;
class UDecalComponent;
class UParticleSystem;

UCLASS()
class FPSGAME_API ALaunchPad : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALaunchPad();

protected:
	UFUNCTION()
	void HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	void PlayEffects() const;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	UStaticMeshComponent* StaticMesh;
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	UBoxComponent* CollisionBox;
	UPROPERTY(EditDefaultsOnly, Category = "Effects")
    UParticleSystem* LaunchFX;
	UPROPERTY(EditDefaultsOnly, Category = "Launch")
	float LaunchForce = 1000000;
};
