// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BlackHole.generated.h"

class UStaticMeshComponent;
class USphereComponent;

UCLASS()
class FPSGAME_API ABlackHole : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABlackHole();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* EventHorizon;
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* Singularity;
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* AttractionSphere;

	UPROPERTY(EditDefaultsOnly, Category = "Physics")
	float GraviryForce = 2000.f;
};
