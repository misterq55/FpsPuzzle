// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponActor.h"
#include "GunActor.generated.h"

/**
 * 
 */
UCLASS()
class FPSPUZZLE_API AGunActor : public AWeaponActor
{
	GENERATED_BODY()
	
private:
	FVector GunMuzzle;

public:
	AGunActor();

public:
	FVector GunMuzzleLocation() {
		return GetActorLocation() + GunMuzzle;
	}
};
