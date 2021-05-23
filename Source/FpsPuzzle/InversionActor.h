// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InversionActor.generated.h"

class UInversionComponent;

UCLASS()
class FPSPUZZLE_API AInversionActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInversionActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;
	
public:
	void OnInversionActorHit(FHitResult HitResult, FVector ForwardVector);
	void SetIsHit(bool InIsHit) { IsHit = InIsHit; }

	bool GetIsHit() {
		return IsHit;
	}

	void SetIsInversed(bool InIsInversed) { IsInversed = InIsInversed; }

	bool GetIsInversed() {
		return IsInversed;
	}

	UMeshComponent* GetMesh() {
		return Mesh;
	}

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere, Category = Mesh)
		UMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, Category = Inversion)
		UInversionComponent* InversionComponent;

	bool IsHit;
	bool IsInversed;
};
